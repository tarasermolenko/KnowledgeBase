/* 
Creator Info
------------
Name : Taras Ermolenko 
Email: taras_ermolenko@sfu.ca

*/
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netdb.h>
#include <gtk/gtk.h>

#include "list.h"
#include "listmutex.h"

// Can change message size based on what is needed
#define MAX_MSG_LEN 300
#define CYPHER_KEY 3

int sock, ret;
struct sockaddr_in remote_addr, local_addr;
char recv_buf[MAX_MSG_LEN];
char send_buf[MAX_MSG_LEN];
int recv_len;
socklen_t remote_addr_len = sizeof(remote_addr);
socklen_t local_addr_len = sizeof(local_addr);

pthread_t receive_thread;
pthread_t send_thread;
pthread_t read_thread;

static pthread_mutex_t outgoing_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t incoming_mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t outgoing_cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t incoming_cond = PTHREAD_COND_INITIALIZER;

int exit_cond;


void *receive_messages(void *arg);

void *send_messages(void *arg);

void *read_messages(void *arg);

GtkWidget *window, *text_view, *entry;
GtkTextBuffer *buffer;

void exit_button_clicked_cb(GtkWidget *widget, gpointer data) {
    const char *goodbye_message = "Client has left the chat!\n";
    pthread_mutex_lock(&outgoing_mutex);
    char* send_msg = strdup(goodbye_message);
    add_outgoing_message(send_msg);
    pthread_cond_signal(&outgoing_cond);
    pthread_mutex_unlock(&outgoing_mutex);
    // Set the exit condition 
    exit_cond = 1;
    // gtk_main_quit() called in the send_messages thread 

}

// Function to update the GUI with incoming messages
static gboolean update_text_view_incoming(gpointer data) {
    char *text = (char *)data;
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    GtkTextTag *tag = gtk_text_tag_table_lookup(gtk_text_buffer_get_tag_table(buffer), "incoming_color");
    gtk_text_buffer_insert_with_tags(buffer, &end, text, -1, tag, NULL);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);
    free(text);
    return FALSE;
}

// Function to update the GUI with outgoing messages
static gboolean update_text_view_outgoing(gpointer data) {
    char *text = (char *)data;
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    GtkTextTag *tag = gtk_text_tag_table_lookup(gtk_text_buffer_get_tag_table(buffer), "outgoing_color");
    gtk_text_buffer_insert_with_tags(buffer, &end, text, -1, tag, NULL);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);
    free(text);
    return FALSE;
}

void send_button_clicked_cb(GtkWidget *widget, gpointer data) {
    const char *msg = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(msg) > 0) {
        char *formatted_msg = g_strdup_printf("%s", msg);
        pthread_mutex_lock(&outgoing_mutex);
        add_outgoing_message(formatted_msg);  // Add message to be sent over the network
        g_idle_add(update_text_view_outgoing, g_strdup(formatted_msg));  // Also update GUI
        pthread_cond_signal(&outgoing_cond);
        pthread_mutex_unlock(&outgoing_mutex);
        gtk_entry_set_text(GTK_ENTRY(entry), "");  // Clear the entry widget
    }
}

void apply_css(GtkWidget *widget, GtkCssProvider *provider) {
    gtk_style_context_add_provider(gtk_widget_get_style_context(widget),
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void create_gtk_window() {
    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chat App");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Create tags for text colors before loading general CSS
    GtkTextTag *incoming_tag = gtk_text_buffer_create_tag(buffer, "incoming_color", "foreground", "red", NULL);
    GtkTextTag *outgoing_tag = gtk_text_buffer_create_tag(buffer, "outgoing_color", "foreground", "#40E0D0", NULL);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *send_button = gtk_button_new_with_label("Send");
    gtk_box_pack_start(GTK_BOX(vbox), send_button, FALSE, FALSE, 0);
    g_signal_connect(send_button, "clicked", G_CALLBACK(send_button_clicked_cb), NULL);

    GtkWidget *exit_button = gtk_button_new_with_label("Exit");
    gtk_box_pack_start(GTK_BOX(vbox), exit_button, FALSE, FALSE, 0);
    g_signal_connect(exit_button, "clicked", G_CALLBACK(exit_button_clicked_cb), NULL);

    // Apply CSS to the whole window and its child widgets
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "* {"
        "   background-color: #333333;"  // Dark grey background for all elements
        "   color: #FFFFFF;"             // White text color
        "}"
        "textview, entry {"
        "   background-color: #222222;"  // Darker grey for text areas
        "   color: #FFFFFF;"             // Ensure text color is white for readability
        "}"
        "button {"
        "   border: 1px solid #555555;"  // Grey border for buttons
        "   background: #444444;"        // Slightly lighter grey for buttons
        "   color: #FFFFFF;"             // White text for buttons
        "   padding: 6px 12px;"          // Padding inside buttons
        "   border-radius: 4px;"         // Rounded corners for buttons
        "}", -1, NULL);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_widget_show_all(window);
}


void simple_encrypt_decrypt(unsigned char *data, int data_len, unsigned char key) {
    for (int i = 0; i < data_len; i++) {
        data[i] ^= key;
    }
}

int main(int argc, char *argv[]) {
    
    printf("prgoram starting... \n");
    // Check if the number of arguments is correct
    if (argc != 4) {
        printf("Wrong format, please enter: ./chat[my port number] [remote machine name] [remote port number]\n");
        return 1;
    }

    // Storing arguments
    int myPort = atoi(argv[1]);
    char* theirHostname = argv[2];
    char* theirPort = argv[3];

    // hardcoding a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0); // file descriptor for network communication
    if (sock < 0) {
        perror("socket");
        return 1;
    }


    // bind the socket to the local port
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY; // use IP of local machine
    local_addr.sin_port = htons(myPort); // set local port
    ret = bind(sock, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if (ret < 0) {
        perror("bind");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // set up the remote address
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; // UDP uses DGRAM
    hints.ai_protocol = IPPROTO_UDP;   // UDP protocol
    // Look up the address of the remote host
    int ret = getaddrinfo(theirHostname, theirPort, &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return 1;
    }

    // Use the first result to set up the remote address
    memset(&remote_addr, 0, sizeof(remote_addr));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(atoi(theirPort)); // set remote port
    remote_addr.sin_addr = ((struct sockaddr_in *)result->ai_addr)->sin_addr; // set remote address

    ret = connect(sock, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
    if(ret < 0)
    {
        perror("connect");
        return 1;
    }

    // create two lists two store incoming & outgoing msgs
    init_message_lists();

    // Set the recv socket to non-blocking if no messages comming in
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    // initialize mutexes and conditions
    pthread_mutex_init(&outgoing_mutex, NULL);
    pthread_mutex_init(&incoming_mutex, NULL);
    pthread_cond_init(&outgoing_cond, NULL);
    pthread_cond_init(&incoming_cond, NULL);

    
    // program ready to take input
    printf("Program Started: \n");

    // Start the receive thread
    if (pthread_create(&receive_thread, NULL, receive_messages, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&send_thread, NULL, send_messages, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&read_thread, NULL, read_messages, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    create_gtk_window();
    gtk_main();

    // join threads after exit condition
    if(pthread_join(read_thread, NULL) != 0)
    {
        perror("pthread_join");
        return 1;
    }

    if(pthread_join(send_thread, NULL) != 0)
    {
        perror("pthread_join");
        return 1;
    }

    if(pthread_join(receive_thread, NULL) != 0)
    {
        perror("pthread_join");
        return 1;
    }

    // close the socket
    close(sock);

    // free the result of getaddrinfo
    freeaddrinfo(result);

    // free list memory
    shutdown_message_lists();

    // destroy mutex and conditions
    pthread_mutex_destroy(&outgoing_mutex);
    pthread_mutex_destroy(&incoming_mutex);
    pthread_cond_destroy(&outgoing_cond);
    pthread_cond_destroy(&incoming_cond);

    return 0;
}


// receive thread
void *receive_messages(void *arg) {

    unsigned char decrypted_msg[MAX_MSG_LEN];
    int decrypted_len;

    
    while (1) {
        
        if(incoming_list_size() != 50)
        {
            // causes program to stall, will wait forever if there is no message to receive
            recv_len = recvfrom(sock, recv_buf, MAX_MSG_LEN, 0, (struct sockaddr*) &remote_addr, &remote_addr_len);

            if(recv_len >= 0)
            {
                recv_buf[recv_len] = '\0';

                strcpy((char*)decrypted_msg, recv_buf);
                decrypted_len = recv_len;
                simple_encrypt_decrypt(decrypted_msg, decrypted_len, CYPHER_KEY);
                decrypted_msg[decrypted_len] = '\0';

                char* rcvd_msg = malloc(MAX_MSG_LEN);

                strcpy(rcvd_msg, (char*)decrypted_msg);

                add_incoming_message(rcvd_msg);

            }
        }

        // signal reader thread that there is a message to read
        pthread_cond_signal(&incoming_cond);

        if(exit_cond == 1)
        {
            pthread_mutex_unlock(&outgoing_mutex); // prevent send thread deadlock 
            pthread_cond_signal(&outgoing_cond); // prevent send thread deadlock 
            return NULL;
        }
        
    }

    return NULL;
}

// send thread
void *send_messages(void *arg) {
    
    unsigned char encrypted_msg[MAX_MSG_LEN];
    int encrypted_len;

    
    while (1) {
       
        if (outgoing_list_size() != 0)
        {
            // pop message at bottom of list and send it.
            char* outgoing_msg = remove_outgoing_message();
            
            strcpy((char*)encrypted_msg, outgoing_msg);
            encrypted_len = strlen(outgoing_msg);
            simple_encrypt_decrypt(encrypted_msg, encrypted_len, CYPHER_KEY);

            // Send the message to the destination
            if (sendto(sock, encrypted_msg, encrypted_len, 0, (struct sockaddr*) &remote_addr, sizeof(remote_addr)) < 0) {
                perror("sendto");
            }

            // free mem after sending
            free(outgoing_msg);

        }else
        {
            // if no messages to send wait for signal
            pthread_mutex_lock(&outgoing_mutex);
            pthread_cond_wait(&outgoing_cond, &outgoing_mutex);
            pthread_mutex_unlock(&outgoing_mutex);
        } 

        if(exit_cond == 1 && outgoing_list_size() == 0)
        {
            gtk_main_quit();
            return NULL;
        }

    }

    return NULL;
}


// read thread
void *read_messages(void *arg) 
{
    while(1)
    {
        if(incoming_list_size() != 0)
        {
            // put incoming msg on list
            char* recv_msg = remove_incoming_message();

            // write to gui
            g_idle_add(update_text_view_incoming, g_strdup(recv_msg));
    
            // also free mem after sending
            free(recv_msg);
        }
        else
        {
            // if no messages to read wait for signal
            pthread_mutex_lock(&incoming_mutex);
            pthread_cond_wait(&incoming_cond, &incoming_mutex);
            pthread_mutex_unlock(&incoming_mutex); 
        }

        if(exit_cond == 1)
        {
            return NULL;
        }

    }

    return NULL;
}
