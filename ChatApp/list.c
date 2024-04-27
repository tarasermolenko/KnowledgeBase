/* 
Student Info
------------
Name : Taras Ermolenko 
Email: taras_ermolenko@sfu.ca

*/

#include <stdio.h>

#include "list.h"


/*----------------------------------------------------------------------------*/
// Note: Any global variables must be static (internally linked)

// Data that will hold list stack

    // "Must use static allocated array for list nodes and list heads"
    // "Single array of list heads (List structs) 
    // to be the pool of lists the module can support"
    // "Code will link these List and Node structs, 
    // via the pointers they store to create and efficient LL module"
    static List list_array[LIST_MAX_NUM_HEADS];

    // Pointer to first first list used to keep track of stack 
    // instead of using previous pointers
    static List* first_list;

    // Number of total lists allocated
    static int list_count;

/*----------------------------------------------------------------------------*/

// Data that will hold node stack

    // "sinlge array of Node structs to serve as the 
    // pool of nodes shared by all lists"
    static Node node_array[LIST_MAX_NUM_NODES];

    // Pointer to first node in list used to keep track of stack
    static Node* first_node_in_list;

    // Number of total nodes allocated
    static int node_count;

/*----------------------------------------------------------------------------*/

// Track wether pointers have been connected
static bool Is_memory_initialized = false;

/*----------------------------------------------------------------------------*/


// Note to self on Void vs Void*:

// Void - return type for functions taht do not return a value, 
// or parameter type for functions that do not take any arguments
// also used as generic type when casting 
// pointers or memory blocks of unkown type

// Void* - is a pointer type that can point to any type of data. 
// It can hold the adress of any type (can be casted to any pointer type)
// but must make sure to cast pointer to same data type it is pointing to.

/*----------------------------------------------------------------------------*/

// Note to self PRIVATE FUNCTIONS:
// Additional private (internally linked static) functions
// Must not be exposed by .h file per requirement
// (A static function in C is a function that 
// has a scope that is limited ot its object file)

/*----------------------------------------------------------------------------*/

// "one-time non constant time set-up/initilization for data structure 
// when List_Create() called
// creates a single array of node structs 
// to serve as the pool of nodes shared by all lists
// O(N) inital set up allowed
static void Set_up()
{

    // Initialize array for heads
    first_list = &(list_array[0]);

    for (int i=0; i < LIST_MAX_NUM_HEADS-1; i++)
    {
        // dereference second position in array 
        // to set the current next pointer as its address
        // Unecessary to set previous pointer as it is redundant when we can keep track 
        // of stack with pointer to first item
        list_array[i].next = &(list_array[i+1]);
    }

    // set last terminating pointer

    // ****** set first pointer that keeps track of array *****
    list_array[LIST_MAX_NUM_HEADS-1].next = NULL;

    // initialize count to zero
    list_count = 0;


    // Initialize array for nodes
    
    // ****** set first pointer that keeps track of array *****
    first_node_in_list = &(node_array[0]);


    for(int i = 0; i < LIST_MAX_NUM_NODES-1; i++)
    {
        node_array[i].next = &(node_array[i+1]);
    }

    // set last terminating pointer
    node_array[LIST_MAX_NUM_NODES-1].next = NULL;
    
    // initialize count to zero
    node_count = 0;
    
}

/*----------------------------------------------------------------------------*/
// Use stack data structure to keep track of memory remaining/being used
// Everything else past this point is O(1), (other than List_free and List_search)

// return list to stack
static void Push_list_stack(List* list)
{
    // If all lists already deallocated
    if(list_count == 0)
    {
        return;
    }
    
    // remove pointers of deleted list
    list->first = NULL;
    list->last = NULL;
    list->current = NULL;
    // reset node count to zero
    list->size = 0;
    // Memory for this list is freed
    list->isListBeingUsed = false;
    list->OOB = LIST_OOB_START;

    // Connect new list next pointer to existing list
    list->next = first_list;

    // Decrement total list count
    list_count = list_count - 1;

    // Set head/top list pointer to point to new list
    first_list = list;
    
    return;
}

// pop a list of the stack and return pointer to the list
static List* Pop_list_stack()
{
    // If no more memory left (max amount has been allocated)
    if(list_count == LIST_MAX_NUM_HEADS)
    {
        return NULL;
    }

    // temp pointer to head list being poped
    List* temp_list = first_list;

    // set new first/head list
    first_list = temp_list->next;

    // Increment list count
    list_count += 1;


    // Initialize variables
    temp_list->first = NULL;
    temp_list->last = NULL;
    temp_list->size = 0;
    temp_list->current = NULL;
    temp_list->isListBeingUsed = true;
    temp_list->OOB = LIST_OOB_START;

    return temp_list;
}

/*----------------------------------------------------------------------------*/

// Does not return anything
static void Push_node_stack(Node* node)
{

    // If all nodes already deallocated
    if(node_count == 0)
    {
        return;
    }

    // Add new node to top of list
    node->next = first_node_in_list;

    // Initialize prev pointer
    node->previous = NULL;

    // Decrement total node count
    node_count -= 1;

    // Assings head/top node list pointer to new node
    first_node_in_list = node;

}

// Returns a pointer to removed node
static Node* Pop_node_stack()
{
    // If all nodes being used
    if(node_count == LIST_MAX_NUM_NODES)
    {
        return NULL;
    }

    // Pointer to node being deleted
    Node* temp_node = first_node_in_list;

    // Set new first node pointer
    first_node_in_list = temp_node->next;

    // Increment node count
    node_count += 1;

    // Reset pointers to NULL
    temp_node->previous = NULL;
    temp_node->node_item = NULL;

    // Return pointer to deleted node
    return temp_node;
}


/*----------------------------------------------------------------------------*/

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create()
{
    // initialize memory if it is not already
    // before poping a list head of the stack
    // This prevents user from allocating more memory than allowed
    if(Is_memory_initialized == false)
    {
        Set_up();
        // The memory has been initialized
        Is_memory_initialized = true;
    }
    
    if(list_count == LIST_MAX_NUM_HEADS)
    {
        // Max number of heads reached
        return NULL;
    }

    // get a new list of memory stack
    List* new_list = Pop_list_stack();

    // if fails for some reason return NULL
    if(new_list == NULL)
    {
        return NULL;
    }

    // return pointer to a new list
    return new_list;
}


// Returns the number of items (lists) in pList.
int List_count(List* pList)
{
    // Check for NULL pointer
    if(pList == NULL)
    {
        return -1;
    }
    
    int size_of_list = pList->size;

    return size_of_list;
}

// Returns a pointer to the first item in pList 
void* List_first(List* pList)
{
    // Check for NULL pointer
    if(pList == NULL)
    {
        return NULL;
    }

    // Returns NULL and sets current item to NULL if list is empty.
    if(pList->size == 0)
    {
        pList->current = NULL;
        return NULL;
    }

    // Returns a pointer to the first item in pList 
    // and makes the first item the current item.
    pList->current = pList->first;

    void* first_item = pList->first->node_item;
    
    // return void pointer
    return first_item;
}

// Returns a pointer to the last item in pList 
void* List_last(List* pList){
        
    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return NULL;
    }

    // Returns NULL and sets current item to NULL if list is empty.
    if(pList->size == 0)
    {
        pList->current = NULL;
        return NULL;
    }

    // Returns a pointer to the last item in pList 
    // and makes the last item the current item.
    pList->current = pList->last;

    void* last_item = pList->last->node_item;
    
    // return void pointer to item
    return last_item;

}

// Advances pList's current item by one, and returns a pointer to the new current item.
void* List_next(List* pList)
{

    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return NULL;
    }

    // If there is no items in list
    if(pList->size == 0)
    {
        // If this operation advances the current item beyond the end of the pList,
        // a NULL pointer is returned and the current item is set to be beyond end of pList.
        if(pList->OOB == LIST_OOB_START)
        {
            pList->OOB = LIST_OOB_END;
        }
        
        return NULL;
    }

    // If current pointer is null and in beyond start location
    if( (pList->current == NULL) && (pList->OOB == LIST_OOB_START))
    {
        // move in bounds
        pList->current = pList->first;

        return pList->current->node_item;
    }

    // If current pointer is null and past end location
    if( (pList->current == NULL && pList->OOB == LIST_OOB_END) )
    {
        // no point moving further out of bounds thus setting and return NULL
        pList->current = NULL;
        
        return NULL;
    }

    // Current pointer last node case
    if( (pList->current == pList->last) )
    {
        // moves out of bound
        pList->OOB = LIST_OOB_END;
        
        // set current pointer to NULL
        pList->current = NULL;
        
        return NULL;
    }

    // Regular case just advance pointer
    pList->current = pList->current->next;

    // new current item
    void* current_item = pList->current->node_item;

    // Return void pointer to item
    return current_item;

}


// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList)
{
    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return NULL;
    }

    // Empty Case
    if(pList->size == 0)
    {
        // If this operation backs up the current item beyond the start of the pList, a NULL pointer 
        // is returned and the current item is set to be before the start of pList.
        if(pList->OOB == LIST_OOB_END)
        {
            pList->OOB = LIST_OOB_START;
        }
        return NULL;
    }


    // If current pointer is null and list OOB (last item exist, so we can return last item)
    if( (pList->current == NULL) && (pList->OOB == LIST_OOB_END) )
    {
        // set current item to its previous which is the tail node
        pList->current = pList->last;

        return pList->current->node_item;
    } 

    // If we are before starting bounds moving farther from start does nothing
    if( (pList->current == NULL && pList->OOB == LIST_OOB_START) )
    {
        // so set and return NULL
        pList->current = NULL;
        
        return NULL;
    }


    if( (pList->current == pList->first) )
    {
        // prev pointer moves out of bounds past first item
        pList->OOB = LIST_OOB_START;

        pList->current = NULL;
        
        return NULL;
    }


    // Regular case just adjust pointer
    pList->current = pList->current->previous;
    
    void* current_item = pList->current->node_item;

    // Return void pointer to item
    return current_item;

}


// Returns a pointer to the current item in pList.
void* List_curr(List* pList)
{

    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return NULL;
    }

    // Current pointer NULL
    if(pList->current == NULL)
    {
        return NULL;
    }

    // return void pointer to current item
    void* current_item = pList->current->node_item;;

    return current_item;

}


// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem)
{
   
    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return -1;
    }
    
    // No space for new nodes
    if(node_count == LIST_MAX_NUM_NODES)
    {
        return LIST_FAIL;
    }


    // List memory not allocated
    // (so just in case user tries to use pointer to list that has been freed.)
    if(pList->isListBeingUsed == false)
    {
        return LIST_FAIL;
    }

    // Inserting at beginning of list (Empty List)
    if(pList->size == 0)
    {
        //--------------------------
        // Create new node by taking one of the stack
        Node* new_node = Pop_node_stack();
        // set item
        new_node->node_item = pItem;
        //--------------------------
        // set new head point to one new node
        pList->first = new_node;
        // set new tail to point to same thing
        pList->last = new_node;
        // no previous or next items
        new_node->previous = NULL;

        new_node->next = NULL;
        // current is the one new node
        pList->current = new_node;
        // increment size count
        pList->size += 1;

        return LIST_SUCCESS;
    }


    // Inserting after last node
    if(pList->current == pList->last)
    {
        //--------------------------
        // Create new node by taking one of the stack
        Node* new_node = Pop_node_stack();
        // set item
        new_node->node_item = pItem;
        //--------------------------

        // set new tail
        pList->last = new_node;

        // set new nodes previous pointer
        new_node->previous = pList->current;

        // sets new nodes next pointer to NULL
        new_node->next = pList->current->next;

        // set previous nodes next pointer to point to new our new node
        pList->current->next = new_node;        
        
        // This will be NULL for tail case
        if(new_node->next != NULL)
        {
            new_node->next->previous = new_node;
        }
        
        // update current pointer to point to our new node
        pList->current = new_node;

        // Increment list size
        pList->size += 1;

        return LIST_SUCCESS;
    }

    // Inserting after first node
    if(pList->current == pList->first)
    {
        //--------------------------
        // Create new node by taking one of the stack
        Node* new_node = Pop_node_stack();
        // set item
        new_node->node_item = pItem;
        //--------------------------

        // set new nodes previous pointer
        new_node->previous = pList->current;

        // set new nodes next pointer
        new_node->next = pList->current->next;
    
        // set previous nodes next pointer to point to new our new node
        pList->current->next = new_node;

        // set next nodes previous pointer to NULL
        // since in this case we are inserting after a
        // single head node and new node is last in list
        if(new_node->next != NULL)
        {
            new_node->next->previous = new_node;
        }
        
        // update current pointer to point to our new node
        pList->current = new_node;

        // Increment list size
        pList->size += 1;

        return LIST_SUCCESS;
    }
    

    // Inserting after a non-existing node
    if(pList->current == NULL)
    {
        //--------------------------
        // Create new node by taking one of the stack
        Node* new_node = Pop_node_stack();
        // set item
        new_node->node_item = pItem;
        //--------------------------

        
        // If at start of list
        if(pList->OOB == LIST_OOB_START)
        {

            // first should not be NULL else this will segfault
            // this is caught if size equals zero  
            if(pList->first != NULL)
            {
                // no previous node
                new_node->previous = pList->first->previous;

                // next node pointer will be current head
                new_node->next = pList->first;

                // set old heads previous pointer to point to new head
                pList->first->previous = new_node;

                // update list head pointer to new head
                pList->first = new_node;
            }
            else // ideally this does not happen but just in case to avoid segfault caught again
            {
                pList->first = new_node;
                new_node->next = NULL;
                new_node->previous = NULL;
                pList->current = new_node;
            }

        }

        // if at end of list
        if(pList->OOB == LIST_OOB_END)
        {

            // last should not be NULL else this will segfault
            // this is caught if size equals zero
            if(pList->last != NULL)
            {
                //set new nodes next pointer to NULL since its last node
                new_node->next = pList->last->next;

                // set new nodes prev pointer to lists tail
                new_node->previous = pList->last;

                // old tail next pointer points to new node
                pList->last->next = new_node;
                
                // update tail pointer to ponit to new node
                pList->last = new_node;
            }
            else // ideally this does not happen but just in case to avoid segfault caught again
            {
                pList->last = new_node;
                new_node->next = NULL;
                new_node->previous = NULL;
                pList->current = new_node;
            }
        }

        // update current pointer and return
        pList->current = new_node;

        pList->size += 1;

        return LIST_SUCCESS;
    }

    //-------------------------------------------------------------
    // (Regular case) Inserting in middle of two existing nodes
    
    // Create new node by taking one of the stack
    Node* new_node = Pop_node_stack();
    // set item
    new_node->node_item = pItem;

    // set new nodes previous pointer
    new_node->previous = pList->current;

    // set new nodes next pointer
    new_node->next = pList->current->next;

    // set previous nodes next pointer to point to new our new node
    pList->current->next = new_node;

    // Edge case: Inserting after a node with a NULL pointer
    // This should not happen unless inserting after tail node which is already
    // caught above
    // set next nodes previous pointer to point to our new node if it not null
    if(new_node->next != NULL)
    {
        new_node->next->previous = new_node;
    }

    // update current pointer to point to our new node
    pList->current = new_node;

    // Increment list size
    pList->size += 1;
    
    return LIST_SUCCESS;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem)
{
    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return -1;
    }
    
    // No space for new nodes
    if(node_count == LIST_MAX_NUM_NODES)
    {
        return LIST_FAIL;
    }

    List_prev(pList);

    int result = List_insert_after(pList,pItem);
    
    return result;

}


// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem)
{
    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return -1;
    }

    // If list full
    if(node_count == LIST_MAX_NUM_NODES)
    {
        return LIST_FAIL;
    }

    pList->current = pList->last;

    int result = List_insert_after(pList,pItem);

    return result;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem)
{

    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return -1;
    }

    // If list full
    if(node_count == LIST_MAX_NUM_NODES)
    {
        return LIST_FAIL;
    }

    pList->current = pList->first;

    int result = List_insert_before(pList,pItem);

    return result;

}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList)
{

    // Check for NULL pointer althought assumed this is never the case
    if(pList == NULL)
    {
        return NULL;
    }

    // If list empty
    if(pList->size == 0 || node_count == 0)
    {
        return NULL;
    }


    if(pList->current == NULL)
    {
        return NULL;
    }

    // temp node to be removed
    Node* temp_node = pList->current;

    void* temp_item = pList->current->node_item;
    
    if(pList->size == 1)
    {
        pList->first = NULL;

        pList->last = NULL;

        pList->current = NULL;
        // since list remove makes next item current one, removing last
        // ndoe should put list in LIST_OOB_END post#53
        pList->OOB = LIST_OOB_END;

        pList->size = 0;
        // free memory back to stack
        Push_node_stack(temp_node);

        return temp_item;
    }

    pList->size -= 1;

    // if removing head
    if(pList->current == pList->first)
    {
        pList->first = pList->first->next;

        pList->first->previous = NULL;

    }
                     
    // if removing tail
    if(pList->current == pList->last)
    {
        pList->last = pList->last->previous;

        pList->current->next = NULL;

        pList->OOB = LIST_OOB_END;

    }

    // set prev pointer of node after one removed
    if(pList->current->next != NULL)
    {
        pList->current->next->previous = temp_node->previous;
    }
   
    // set next pointer of node before one removed
    if(pList->current->previous != NULL)
    {
        
        pList->current->previous->next = temp_node->next;
    }

    // Update currnet pointer
    pList->current = pList->current->next;

    // free memory back to stack
    Push_node_stack(temp_node);

    // return void pointer
    return temp_item;
}


// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList)
{
    // Check for NULL pointer
    if(pList == NULL)
    {
        return NULL;
    }

    // If list empty
    if(pList->size == 0 || node_count == 0)
    {
        return NULL;
    }

    // set current to last for trim
    pList->current = pList->last;

    if(pList->current == NULL)
    {
        return NULL;
    }

    // temp node to be removed
    Node* temp_node = pList->current;

    void* temp_item = pList->current->node_item;
    
    if(pList->size == 1)
    {
        pList->first = NULL;

        pList->last = NULL;

        pList->current = NULL;

        // if trim function passed on a single node current item gets set
        // beyond start of the list - Harinder K Post #22
        pList->OOB = LIST_OOB_START;

        pList->size = 0;
        // free memory back to stack
        Push_node_stack(temp_node);

        return temp_item;
    }

    pList->size -= 1;

    // if removing head in this case should be if only a single node so should
    // not be executed unless something went wrong
    if(pList->current == pList->first)
    {
        pList->first = pList->first->next;

        pList->first->previous = NULL;

        pList->OOB = LIST_OOB_START;

    }
                     
    // if removing tail
    if(pList->current == pList->last)
    {
        pList->last = pList->last->previous;

        pList->current->next = NULL;

    }

    // set prev pointer of node after one removed
    if(pList->current->next != NULL)
    {
        pList->current->next->previous = temp_node->previous;
    }
   
    // set next pointer of node before one removed
    if(pList->current->previous != NULL)
    {
        
        pList->current->previous->next = temp_node->next;
    }

    // Update currnet pointer
    pList->current = pList->current->next;

    // free memory back to stack
    Push_node_stack(temp_node);

    // return void pointer
    return temp_item;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2)
{
    // Check for NULL pointers
    if(pList1 == NULL || pList2 == NULL)
    {
        return;
    }

    // if second list empty
    if(pList2->size == 0)
    {
        // push list2 mem back on stack
        // dont need to free since size is zero
        Push_list_stack(pList2);
        
        return;
    }

    // if first list empty
    if(pList1->size == 0)
    {
        // adjust list 1 pointers
        pList1->first = pList2->first;

        pList1->last = pList2->last;

        // update list 1 size
        pList1->size = pList2->size;

        // if first list empty, current pointer would be null
        // new list inherits OOB_START  state post#44
        pList1->OOB = LIST_OOB_START;

        // push list 2 back on stack, no need to free since its node are 
        // being used/tracked by list 1.
        Push_list_stack(pList2);
        
        return;
    }

    // connect pList1 tail to first node in pList2
    pList1->last->next = pList2->first;
    
    // conect pList2 head to pList1 tail
    pList2->first->previous = pList1->last;

    // set new tail for pList2
    pList1->last = pList2->last;

    // combine the size count
    pList1->size += pList2->size;

    // push list mem back on stack, no need to free nodes.
    Push_list_stack(pList2);
    
    // Returns list 1 with new connected nodes, retaining same current pointer and OOB state
    return;
}


// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn)
{

    // Check for NULL pointer
    if(pList == NULL)
    {
        return;
    }

    // catches if user tries to free list that has already been freed
    if(pList->isListBeingUsed == false)
    {
        return;
    }

    pList->current = pList->first;

    // Push nodes back to memeory stack
    while(pList->current != NULL)
    {
        Node* temp = pList->current;
        
        pList->current = pList->current->next;

        
        // Implemented on Client side
        if(pItemFreeFn != NULL)
        {
            (*pItemFreeFn)(temp->node_item);
        }
        
        // Free each node
        Push_node_stack(temp);
    }

    // Push list back on list stack
    Push_list_stack(pList);

    return;
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. 

// ***This parameter is a pointer to a routine that takes as its first argument an item pointer, 
// and as its second argument pComparisonArg. ***
// Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg)
{
    // Check for NULL pointer
    if(pList == NULL)
    {
        return NULL;
    }

    if(pList->isListBeingUsed == false)
    {
        return NULL;
    }

    if(pComparator == NULL)
    {
        return NULL;
    }
    
    if(pList->size == 0)
    {
        return NULL;
    }

    if(pList->current == NULL && pList->OOB == LIST_OOB_END)
    {
        return NULL;
    }

    if(pList->current == NULL && pList->OOB == LIST_OOB_START)
    {
        // sets current pointer to first item in list
        List_next(pList);
    }

    // Search pList, starting at the current item
    while (pList->current != NULL)
    {
        // deref pointer comparator routine
        if( (*pComparator)(pList->current->node_item, pComparisonArg) )
        {
            return pList->current->node_item;
        }

        pList->current = pList->current->next;
    }

    // if match not found and we reach end
    pList->OOB = LIST_OOB_END;

    return NULL;
}