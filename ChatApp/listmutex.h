#ifndef _LISTMUTEX_H
#define _LISTMUTEX_H

#include "list.h"

// this will be the monitor to manage shared memory CS access to the message lists
int add_outgoing_message(char* message);

char* remove_outgoing_message();

int outgoing_list_size();


int add_incoming_message(char* message);

char* remove_incoming_message();

int incoming_list_size();


void init_message_lists();

void shutdown_message_lists();

typedef void (*FREE_FN)(void* pItem);
void FreeRoutine(void* pItem);

#endif