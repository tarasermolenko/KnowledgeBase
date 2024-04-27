#include <pthread.h>
#include <stdlib.h>

#include "listmutex.h"

// using 2 lists to manage incoming and outgoing messages
List* list_incoming_messages;
List* list_outgoing_messages;

static pthread_mutex_t outgoing_msg_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t incoming_msg_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function that frees list item memory
typedef void (*FREE_FN)(void* pItem);
void FreeRoutine(void* pItem)
{
    free(pItem);
}


int add_outgoing_message(char* message)
{
    int return_val;

    pthread_mutex_lock(&outgoing_msg_mutex);
    {
        // add item to top of stack
        return_val = List_prepend(list_outgoing_messages, message);
    }
    pthread_mutex_unlock(&outgoing_msg_mutex);

    return return_val;
}

char* remove_outgoing_message()
{
    char* msg;
    
    // remove item from bottom of stack
    pthread_mutex_lock(&outgoing_msg_mutex);
    {
        // add item to top of stack
        msg = List_trim(list_outgoing_messages);

    }
    pthread_mutex_unlock(&outgoing_msg_mutex);

    return msg;
}

int outgoing_list_size()
{
    int msg_count;

    pthread_mutex_lock(&outgoing_msg_mutex);
    {
        // returns size of list
        msg_count = List_count(list_outgoing_messages);
    }
    pthread_mutex_unlock(&outgoing_msg_mutex);

    return msg_count;
}

int add_incoming_message(char* message)
{
    int return_val;

    pthread_mutex_lock(&incoming_msg_mutex);
    {
        // add item to top of stack
        return_val = List_prepend(list_incoming_messages, message);
    }
    pthread_mutex_unlock(&incoming_msg_mutex);

    return return_val;
}

char* remove_incoming_message()
{
    char* msg;
    
    // remove item from bottom of stack
    pthread_mutex_lock(&incoming_msg_mutex);
    {
        // add item to top of stack
        msg = List_trim(list_incoming_messages);
    }
    pthread_mutex_unlock(&incoming_msg_mutex);

    return msg;
}

int incoming_list_size()
{
    int msg_count;

    pthread_mutex_lock(&outgoing_msg_mutex);
    {
        // returns size of list
        msg_count = List_count(list_incoming_messages);
    }
    pthread_mutex_unlock(&outgoing_msg_mutex);

    return msg_count;
}


void init_message_lists()
{
    // initialize list
    list_incoming_messages = List_create();
    list_outgoing_messages = List_create();
    // initialize mutex
    pthread_mutex_init(&incoming_msg_mutex, NULL);
    pthread_mutex_init(&outgoing_msg_mutex, NULL);


}

void shutdown_message_lists()
{
    // free list memory
    List_free(list_incoming_messages, FreeRoutine);
    List_free(list_outgoing_messages, FreeRoutine);
    // destroy mutex
    pthread_mutex_destroy(&incoming_msg_mutex);
    pthread_mutex_destroy(&outgoing_msg_mutex);
}