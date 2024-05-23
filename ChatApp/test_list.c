#include "list.c"
#include <assert.h>

typedef void (*FREE_FN)(void* pItem);

void FreeRoutine(void* pItem)
{
    pItem = NULL;
}

typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);

bool CompareRoutine(void* pItem, void* pComparisonArg)
{
    int *item1 = pItem;
    int *item2 = pComparisonArg;

    if( *item1 != *item2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void test_list_create();
void test_list_count();
void test_list_first_and_last();
void test_list_next_prev_and_current();
void test_list_insert_after_and_before();
void test_list_append_and_prepend();
void test_list_remove();
void test_list_trim();
void test_list_concat();
void test_list_search();

int main() 
{

    printf("List Test Program\n\n");
    
    test_list_create();
    test_list_count();
    test_list_first_and_last();
    test_list_next_prev_and_current();
    test_list_insert_after_and_before();
    test_list_append_and_prepend();
    test_list_remove();
    test_list_trim();
    test_list_concat();
    test_list_search();

    printf("List Test Program Finished \n\n");
    return 0;

};


void test_list_create()
{
    // Testing List Initialization
    printf("Running Initilization Tests\n");
    List* List_1 = List_create();
    List* List_2 = List_create();
    List* List_3 = List_create();
    List* List_4 = List_create();
    List* List_5 = List_create();
    List* List_6 = List_create();
    List* List_7 = List_create();
    List* List_8 = List_create();
    List* List_9 = List_create();
    List* List_10 = List_create();
    List* List_11 = List_create();



    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }
    
    if(List_2 != NULL)
    {
        printf("List 2 Created Successfully\n");
    }
    else
    {
        printf("List 2 Create Failed\n");
    }

    if(List_3 != NULL)
    {
        printf("List 3 Created Successfully\n");
    }
    else
    {
        printf("List 3 Create Failed\n");
    }

    if(List_4 != NULL)
    {
        printf("List 4 Created Successfully\n");
    }
    else
    {
        printf("List 4 Create Failed\n");
    }

    if(List_5 != NULL)
    {
        printf("List 5 Created Successfully\n");
    }
    else
    {
        printf("List 5 Create Failed\n");
    }
    
    if(List_6 != NULL)
    {
        printf("List 6 Created Successfully\n");
    }
    else
    {
        printf("List 6 Create Failed\n");
    }

    if(List_7 != NULL)
    {
        printf("List 7 Created Successfully\n");
    }
    else
    {
        printf("List 7 Create Failed\n");
    }

    if(List_8 != NULL)
    {
        printf("List 8 Created Successfully\n");
    }
    else
    {
        printf("List 8 Create Failed\n");
    }

    if(List_9 != NULL)
    {
        printf("List 9 Created Successfully\n");
    }
    else
    {
        printf("List 9 Create Failed\n");
    }

    if(List_10 != NULL)
    {
        printf("List 10 Created Successfully\n");
    }
    else
    {
        printf("List 10 Create Failed\n");
    }

    if(List_11 == NULL)
    {
        printf("List 11 Not Created Becouse Max Heads Reached Successfully\n");
    }
    else
    {
        printf("List 11 Created, Something Failed\n");
    }







    List_free(List_1, FreeRoutine);
    List_free(List_2, FreeRoutine);
    List_free(List_3, FreeRoutine);
    List_free(List_4, FreeRoutine);
    List_free(List_5, FreeRoutine);
    List_free(List_6, FreeRoutine);
    List_free(List_7, FreeRoutine);
    List_free(List_8, FreeRoutine);
    List_free(List_9, FreeRoutine);

    List* List_12 = List_create();
    if(List_12 != NULL)
    {
        printf("List 12 Created Successfuly after all others freed\n");
    }
    else
    {
        printf("List 12 Not Created, Something Failed\n");
    }

    List_free(List_12, FreeRoutine);

    printf("Initilization Tests End\n");
    printf("\n\n");
}

void test_list_count()
{   
    printf("Running Count Tests\n");

    List* List_1 = List_create();
    
    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }

    int count = List_count(List_1);
    
    if(count == 0)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }

    int item = 10;
    int item2 = 11;
    int item3 = 12;
    int item4 = 13;
    int item5 = 14;
    int item6 = 15;

    
    List_insert_after(List_1, (void*)&item);
    
    List_insert_after(List_1, (void*)&item2);
    List_insert_after(List_1, (void*)&item3);
    List_insert_after(List_1, (void*)&item4);
    List_insert_after(List_1, (void*)&item5);
    List_insert_after(List_1, (void*)&item6);

    int count2 = List_count(List_1);
    if(count2 == 6)
    {
        printf("Passed\n");
    }
    else
    {
        printf("Failed\n");
    }


    FREE_FN FreeRoutine; 
    List_free(List_1, FreeRoutine);
    
    printf("Count Tests End\n");

}

void test_list_first_and_last()
{
    printf("Running First and Last Tests\n");

    List* List_1 = List_create();

    List* List_2 = List_create();
    
    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }

    if(List_2 != NULL)
    {
        printf("List 2 Created Successfully\n");
    }
    else
    {
        printf("List 2 Create Failed\n");
    }

    int item = 10;
    int item2 = 11;
    int item3 = 12;
    int item4 = 13;
    int item5 = 14;
    int item6 = 15;

    int *result;

    List_insert_after(List_1, (void*)&item);
    List_insert_after(List_1, (void*)&item2);
    List_insert_after(List_1, (void*)&item3);
    List_insert_after(List_1, (void*)&item4);
    List_insert_after(List_1, (void*)&item5);
    List_insert_after(List_1, (void*)&item6);

    result = List_first(List_1);

    if(*result == 10)
    {
        printf("List_first passed\n");
    }
    else
    {
        printf("List_first failed\n");
    }


    result = List_last(List_1);

    if(*result == 15)
    {
        printf("List_last passed\n");
    }
    else
    {
        printf("List_last failed\n");
    }

    result = List_first(List_2);

    if(result == NULL)
    {
        printf("List_first NULL passed\n");
    }
    else
    {
        printf("List_last NULL failed\n");
    }

    result = List_last(List_2);

    if(result == NULL)
    {
        printf("List_last  NULL passed\n");
    }
    else
    {
        printf("List_last NULL failed\n");
    }



    FREE_FN FreeRoutine; 
    List_free(List_1, FreeRoutine);
    List_free(List_2, FreeRoutine);

    printf("List First and Last Tests Passed\n\n");
}

void test_list_next_prev_and_current()
{
    printf("Running List Next, Prev and Current Tests\n");

    List* List_1 = List_create();

    List* List_2 = List_create();
    
    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }

    if(List_2 != NULL)
    {
        printf("List 2 Created Successfully\n");
    }
    else
    {
        printf("List 2 Create Failed\n");
    }

    int item = 10;
    int item2 = 11;
    int item3 = 12;
    int item4 = 13;
    int item5 = 14;
    int item6 = 15;

    int *result;

    List_insert_after(List_1, (void*)&item);
    List_insert_after(List_1, (void*)&item2);
    List_insert_after(List_1, (void*)&item3);
    List_insert_after(List_1, (void*)&item4);
    List_insert_after(List_1, (void*)&item5);
    List_insert_after(List_1, (void*)&item6);

    result = List_prev(List_1);

    if(*result == 14)
    {
        printf("List_prev passed\n");
    }
    else
    {
        printf("List_prev failed\n");
    }
    
    result = List_next(List_1);
    printf("%i\n",*result);

    if(*result == 15)
    {
        printf("List_prev passed\n");
    }
    else
    {
        printf("List_prev failed\n");
    }

    result = List_next(List_1);

    if(result == NULL)
    {
        printf("List_next NULL passed\n");
    }
    else
    {
        printf("List_next NULL failed\n");
    }

    result = List_prev(List_1);
    printf("%i\n",*result);
    result = List_prev(List_1);
    printf("%i\n",*result);
    result = List_prev(List_1);
    printf("%i\n",*result);
    result = List_prev(List_1);
    printf("%i\n",*result);
    result = List_prev(List_1);
    printf("%i\n",*result);
    result = List_prev(List_1);
    printf("%i\n",*result);
    result = List_prev(List_1);

    if(result == NULL)
    {
        printf("List_prev NULL passed\n");
    }
    else
    {
        printf("List_prev NULL failed\n");
    }

    result = List_curr(List_1);

    if(result == NULL)
    {
        printf("List_curr NULL passed\n");
    }
    else
    {
        printf("List_curr NULL failed\n");
    }


    result = List_next(List_1);
    printf("%i\n",*result);

    result = List_curr(List_1);
    printf("%i\n",*result);

    result = List_next(List_1);
    printf("%i\n",*result);

    result = List_curr(List_1);
    printf("%i\n",*result);

    FREE_FN FreeRoutine; 
    List_free(List_1, FreeRoutine);
    List_free(List_2, FreeRoutine);

    printf("List Next, Prev and Current Tests Passed\n\n");

}

void test_list_insert_after_and_before()
{

    printf("Running List Insert, After and Before Tests\n");

    List* List_1 = List_create();

    List* List_2 = List_create();
    
    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }

    if(List_2 != NULL)
    {
        printf("List 2 Created Successfully\n");
    }
    else
    {
        printf("List 2 Create Failed\n");
    }

    int item = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    int item5 = 5;
    int item6 = 6;
    int item7 = 7;

    int *result;

    // 1
    List_insert_after(List_1, (void*)&item);
    
    result = List_curr(List_1);
    printf("%i\n",*result);

    // 2
    List_insert_after(List_1, (void*)&item2);
    
    result = List_curr(List_1);
    printf("%i\n",*result);

    // 3
    List_insert_after(List_1, (void*)&item3);
    
    result = List_curr(List_1);
    printf("%i\n",*result);

    printf("\n");

    result = List_curr(List_1);
    printf("%i\n",*result);    

    result = List_prev(List_1);
    printf("%i\n",*result);

    result = List_prev(List_1);
    printf("%i\n",*result);

    printf("\n");

    result = List_curr(List_1);
    printf("%i\n",*result);

    printf("\n");


    List_insert_before(List_1, (void*)&item4);
    
    result = List_curr(List_1);
    printf("%i\n",*result);

    List_insert_before(List_1, (void*)&item5);
    
    result = List_curr(List_1);
    printf("%i\n",*result);

    List_insert_before(List_1, (void*)&item6);
    
    result = List_curr(List_1);
    printf("%i\n",*result);

      printf("\n\n");

    result = List_curr(List_1);
    printf("%i\n",*result);
    assert(*result == 6); 

    result = List_next(List_1);
    printf("%i\n",*result);
    assert(*result == 5); 
    
    result = List_next(List_1);
    printf("%i\n",*result);
    assert(*result == 4); 

    result = List_next(List_1);
    printf("%i\n",*result);
    assert(*result == 1); 

    result = List_next(List_1);
    printf("%i\n",*result);
    assert(*result == 2); 

    result = List_next(List_1);
    printf("%i\n",*result);
    assert(*result == 3); 

    printf("\n\n");

    /////////
     printf("List 2\n\n");

    List_insert_before(List_2, (void*)&item4);
    result = List_curr(List_2);
    printf("%i\n",*result);
    List_insert_before(List_2, (void*)&item3);
    result = List_curr(List_2);
    printf("%i\n",*result);
    List_insert_before(List_2, (void*)&item2);
    result = List_curr(List_2);
    printf("%i\n",*result);
    List_insert_before(List_2, (void*)&item);
    result = List_curr(List_2);
    printf("%i\n",*result);

    printf("\n\n");

    result = List_curr(List_2);
    printf("%i\n",*result);

    result = List_next(List_2);
    printf("%i\n",*result);

    result = List_next(List_2);
    printf("%i\n",*result);

    result = List_next(List_2);
    printf("%i\n",*result);

    result = List_prev(List_2);
    printf("%i\n",*result);

    result = List_prev(List_2);
    printf("%i\n",*result);

    result = List_prev(List_2);
    printf("%i\n",*result);

    List_free(List_1, FreeRoutine);
    List_free(List_2, FreeRoutine);

    printf("here\n");

    List_1 = List_create();
    assert(List_1 != NULL); 

    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }

    printf("\n");
    
    List_insert_before(List_1, (void*)&item);
    List_insert_after(List_1, (void*)&item3);
    List_insert_before(List_1, (void*)&item2);
    List_next(List_1);
    List_insert_after(List_1, (void*)&item6);
    List_insert_before(List_1, (void*)&item5);
    List_insert_before(List_1, (void*)&item4);
    List_next(List_1);
    List_next(List_1);
    
    // Expected Output: 6,5,4,3,2,1
    result = List_curr(List_1);
    printf("%i\n",*result);
    assert(*result == 6); 

    result = List_prev(List_1);
    printf("%i\n",*result);
    assert(*result == 5); 

    result = List_prev(List_1);
    printf("%i\n",*result);
    assert(*result == 4); 

    result = List_prev(List_1);
    printf("%i\n",*result);
    assert(*result == 3); 

    result = List_prev(List_1);
    printf("%i\n",*result);
    assert(*result == 2); 

    result = List_prev(List_1);
    printf("%i\n",*result);
    assert(*result == 1); 

    List_free(List_1, FreeRoutine);

    printf("Finished List Next, Prev and Current Tests\n");
    
}

void test_list_append_and_prepend()
{

    printf("Running append and prepend Tests\n");

    List* List_1 = List_create();

    int item = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    int item5 = 5;
    int item6 = 6;
    int item7 = 7;

    int *result;

    List_append(List_1, (void*)&item2);
    result = List_curr(List_1);
    assert(*result == 2);

    List_append(List_1, (void*)&item3);
    result = List_curr(List_1);
    assert(*result == 3);

    List_prepend(List_1, (void*)&item);
    result = List_curr(List_1);
    assert(*result == 1);

    result = List_next(List_1);
    assert(*result == 2);

    result = List_next(List_1);
    assert(*result == 3);

    List_free(List_1, FreeRoutine);

    printf("Finished append and prepend Tests\n");
    
}

void test_list_remove()
{
    printf("Running List Remove Tests\n");

    List* List_1 = List_create();

    int item = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    int item5 = 5;
    int item6 = 6;
    int item7 = 7;

    int *result;

    List_append(List_1, (void*)&item2);
    result = List_curr(List_1);
    assert(*result == 2);

    List_append(List_1, (void*)&item3);
    result = List_curr(List_1);
    assert(*result == 3);

    List_prepend(List_1, (void*)&item);
    result = List_curr(List_1);
    assert(*result == 1);

    result = List_next(List_1);
    assert(*result == 2);

    result = List_next(List_1);
    assert(*result == 3);

    int count = List_count(List_1);
    printf("%i\n",count);

    result = List_remove(List_1);
    assert(*result == 3);

    count = List_count(List_1);
    printf("%i\n",count);

    result = List_curr(List_1);
    assert(result == NULL);

    result = List_prev(List_1);
    assert(*result == 2);

    result = List_prev(List_1);
    assert(*result == 1);

    result = List_remove(List_1);
    assert(*result == 1);

    count = List_count(List_1);
    printf("%i\n",count);

    result = List_remove(List_1);
    assert(*result == 2);

    count = List_count(List_1);
    printf("%i\n",count);

    List_append(List_1, (void*)&item2);
    result = List_curr(List_1);
    assert(*result == 2);

    List_append(List_1, (void*)&item3);
    result = List_curr(List_1);
    assert(*result == 3);

    result = List_remove(List_1);
    assert(*result == 3);


    count = List_count(List_1);
    assert(count == 1);

    List_free(List_1, FreeRoutine);

    printf("Finished List Remove Tests\n");
}

void test_list_trim()
{
    printf("Running List Trim Tests\n");

    List* List_1 = List_create();

    int item = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    int item5 = 5;
    int item6 = 6;
    int item7 = 7;

    int *result;

    List_append(List_1, (void*)&item3);
    result = List_curr(List_1);
    assert(*result == 3);

    List_append(List_1, (void*)&item4);
    result = List_curr(List_1);
    assert(*result == 4);

    List_append(List_1, (void*)&item5);
    result = List_curr(List_1);
    assert(*result == 5);
    
    result = List_trim(List_1);
    printf("%i \n", *result);

    result = List_trim(List_1);
    printf("%i \n", *result);

    result = List_trim(List_1);
    printf("%i \n", *result);

    result = List_trim(List_1);
    assert(result == NULL);

    List_free(List_1, FreeRoutine);

    printf("Finished Running List Trim Tests\n\n");

}

void test_list_concat()
{
    printf("Running List Concat Tests\n");

    List* List_1 = List_create();

    List* List_2 = List_create();
    
    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }

    if(List_2 != NULL)
    {
        printf("List 2 Created Successfully\n");
    }
    else
    {
        printf("List 2 Create Failed\n");
    }

    int item1 = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    int item5 = 5;
    int item6 = 6;
    int item7 = 7;

    int *result;

    List_append(List_1, (void*)&item1);
    result = List_curr(List_1);
    assert(*result == 1);

    List_append(List_1, (void*)&item2);
    result = List_curr(List_1);
    assert(*result == 2);

    List_append(List_1, (void*)&item3);
    result = List_curr(List_1);
    assert(*result == 3);

    List_append(List_2, (void*)&item4);
    result = List_curr(List_2);
    assert(*result == 4);

    List_append(List_2, (void*)&item5);
    result = List_curr(List_2);
    assert(*result == 5);

    List_append(List_2, (void*)&item6);
    result = List_curr(List_2);
    assert(*result == 6);

    List_concat(List_1, List_2);
   
    result = List_curr(List_1);
    assert(*result == 3);
    result = List_next(List_1);
    assert(*result == 4);
    result = List_next(List_1);
    assert(*result == 5);
    result = List_next(List_1);
    assert(*result == 6);
    result = List_next(List_1);
    assert(result == NULL);
    result = List_prev(List_1);
    result = List_prev(List_1);
    result = List_prev(List_1);
    result = List_prev(List_1);
    result = List_prev(List_1);
    assert(*result == 2);
    result = List_prev(List_1);
    assert(*result == 1);
    result = List_prev(List_1);
    assert(result == NULL);

    List_free(List_1, FreeRoutine);
    List_free(List_2, FreeRoutine);

    printf("\nFinished Running List Concat Tests\n\n");
}


void test_list_search()
{
    printf("Running List Search Tests\n\n\n");

    List* List_1 = List_create();

    List* List_2 = List_create();
    
    if(List_1 != NULL)
    {
        printf("List 1 Created Successfully\n");
    }
    else
    {
        printf("List 1 Create Failed\n");
    }

    if(List_2 != NULL)
    {
        printf("List 2 Created Successfully\n");
    }
    else
    {
        printf("List 2 Create Failed\n");
    }

    int item1 = 1;
    int item2 = 2;
    int item3 = 3;
    int item4 = 4;
    int item5 = 5;
    int item6 = 6;
    int item7 = 7;

    int *result;

    List_append(List_1, (void*)&item1);
    result = List_curr(List_1);
    assert(*result == 1);

    List_append(List_1, (void*)&item2);
    result = List_curr(List_1);
    assert(*result == 2);

    List_append(List_1, (void*)&item3);
    result = List_curr(List_1);
    assert(*result == 3);

    List_append(List_1, (void*)&item4);
    result = List_curr(List_1);
    assert(*result == 4);

    List_append(List_1, (void*)&item5);
    result = List_curr(List_1);
    assert(*result == 5);

    List_append(List_1, (void*)&item6);
    result = List_curr(List_1);
    assert(*result == 6);

    result = List_prev(List_1);
    assert(result != NULL);

    result = List_prev(List_1);
    assert(result != NULL);

    result = List_prev(List_1);
    assert(result != NULL);

    result = List_prev(List_1);
    assert(result != NULL);

    result = List_prev(List_1);
    assert(result != NULL);

    
    int itemtolookfor = 4;
    void *search = &itemtolookfor;
    int *found;

    found = List_search(List_1, CompareRoutine, search);
    assert(*found == 4);

    itemtolookfor = 5;

    found = List_search(List_1, CompareRoutine, search);
    assert(*found == 5);
    

    itemtolookfor = 6;

    found = List_search(List_1, CompareRoutine, search);
    assert(*found == 6);

    itemtolookfor = 1;

    found = List_search(List_1, CompareRoutine, search);
    assert(found == NULL);

    printf("Finished Running List Search Tests\n\n\n\n\n");
}
