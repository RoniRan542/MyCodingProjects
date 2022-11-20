/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Name: Tom Avi-yaakov
Reviewer: 
Date: 19.05.22
File: Data Structures - Heap
Description: Implementing Heap
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#include <stdio.h> /*printf*/

#include "heap.h"

#define RUNTEST(test) {\
            if (!test)\
            {\
                printf("\x1b[0;34m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;35m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

enum return_status
{
	BOOL_FALSE = 0,
	BOOL_TRUE = 1,
	SUCCESS = 0,
	FAILURE = 1,
	ERROR = -1
};

static int ValCheck(int recieved_val, int expected_val, int line);
static int IntCmp(const void *new_data, const void *tree_data, void *param);
static int CreatDestroy();
static int InsertTest();

static int StructCmp(const void *new_data, const void *tree_data, void *param);
static int IsMatchStruct(const void *data, const void *heap_data, void *param);
static int InsertTestStruct();
static int RemoveStruct();
static int PeekPopTestStruct();

int g_total_fails = 0;


int main()
{
	RUNTEST(CreatDestroy());
	RUNTEST(InsertTest());
	RUNTEST(InsertTestStruct());
	RUNTEST(RemoveStruct());
	RUNTEST(PeekPopTestStruct());
	
	
	if (0 < g_total_fails)
	{
		printf("\n\n****** TOTAL FAILS = %d ******\n\n", g_total_fails);
	}
	
	return 0;
}

static int ValCheck(int recieved_val, int expected_val, int line)
{
	if (recieved_val != expected_val)
	{
		printf("----------------FAIL line %d----------------\n", line);
		printf("got %d, when wanted %d\n",recieved_val, expected_val);
		++g_total_fails;
		return 1;
	}
	return 0;
}

static int IntCmp(const void *new_data, const void *tree_data, void *param)
{
	(void)param;
	return (*(int *)new_data - *(int *)tree_data);
}

static int CreatDestroy()
{
    int status = 0;
    int param = 2;
    heap_t *heap = NULL;
    
    printf("~~~~~~~~~TestCreateDestroy~~~~~~~~~\n");
    
    heap = HeapCreate(&IntCmp, &param);
    status += ValCheck(NULL != heap, BOOL_TRUE,__LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_TRUE, __LINE__);
    status += ValCheck(HeapSize(heap), 0, __LINE__);

    HeapDestroy(heap);
    heap = NULL;
    
    heap = HeapCreate(&IntCmp, &param);
    status += ValCheck(HeapPush(heap, &param), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 1, __LINE__);

    HeapDestroy(heap);
    heap = NULL;
    
    return status;
}

static int InsertTest()
{
    int status = 0;
    int param = 2;
    int a = 100;
    int b = 19;
    int c = 36;
    int d = 17;
    int e = 101;
    int f = 40;
    int g = 7;
    int h = 18;
    
	heap_t *heap = NULL;
	
	printf("~~~~~~~~~TestInsertTest~~~~~~~~~\n");
	
    heap = HeapCreate(&IntCmp, &param);
    status += ValCheck(NULL != heap, BOOL_TRUE,__LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_TRUE, __LINE__);
    status += ValCheck(HeapSize(heap), 0, __LINE__);
	
	PrintHeap(heap);
	status += ValCheck(HeapPush(heap, &a), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 1, __LINE__);
	
	PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &b), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 2, __LINE__);
	
	PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &c), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 3, __LINE__);
	
	PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &d), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 4, __LINE__);

    PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &e), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 5, __LINE__);

    PrintHeap(heap);
    
	status += ValCheck(HeapPush(heap, &f), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 6, __LINE__);

    PrintHeap(heap);
    
	status += ValCheck(HeapPush(heap, &g), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 7, __LINE__);

    PrintHeap(heap);
    
	status += ValCheck(HeapPush(heap, &h), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 8, __LINE__);

    PrintHeap(heap);
	
    HeapDestroy(heap);
    heap = NULL;
    return status;
}

typedef struct element
{
	int elem;
}st_int_t;
    
static int StructCmp(const void *new_data, const void *tree_data, void *param)
{
	(void)param;
	
	return (((struct element *)new_data)->elem - ((struct element *)tree_data)->elem);
}

static int IsMatchStruct(const void *data, const void *heap_data, void *param)
{
	(void)param;   
	/*printf("%d ** %d\n", ((struct element *)data)->elem, ((struct element *)heap_data)->elem);*/
    return  (((struct element *)data)->elem == ((struct element *)heap_data)->elem);
}

static int InsertTestStruct()
{
    int status = 0;
    int param = 2;
    st_int_t a = {100};
    st_int_t b = {19};
    st_int_t c = {36};
	st_int_t d = {17};
    st_int_t e = {101};
	st_int_t f = {40};
	st_int_t g = {7};
	st_int_t h = {18};
    
	heap_t *heap = NULL;
	
	printf("~~~~~~~~~TestInsertTest~~~~~~~~~\n");
	
    heap = HeapCreate(&StructCmp, &param);
    status += ValCheck(NULL != heap, BOOL_TRUE,__LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_TRUE, __LINE__);
    status += ValCheck(HeapSize(heap), 0, __LINE__);
	
	PrintHeap(heap);
	status += ValCheck(HeapPush(heap, &a), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 1, __LINE__);
	
	PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &b), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 2, __LINE__);
	
	PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &c), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 3, __LINE__);
	
	PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &d), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 4, __LINE__);

    PrintHeap(heap);
	
	status += ValCheck(HeapPush(heap, &e), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 5, __LINE__);

    PrintHeap(heap);
    
	status += ValCheck(HeapPush(heap, &f), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 6, __LINE__);

    PrintHeap(heap);
    
	status += ValCheck(HeapPush(heap, &g), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 7, __LINE__);

    PrintHeap(heap);
    
	status += ValCheck(HeapPush(heap, &h), SUCCESS, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 8, __LINE__);

    PrintHeap(heap);
	
    HeapDestroy(heap);
    heap = NULL;

    return status;
}

static int RemoveStruct()
{
    int status = 0;
    int param = 2;
    st_int_t a = {101};
    st_int_t b = {30};
    st_int_t c = {40};
	st_int_t d = {18};
    st_int_t e = {19};
	st_int_t f = {36};
	st_int_t g = {35};
	st_int_t h = {17};
	st_int_t i = {15};
	st_int_t *result = NULL;
    
	heap_t *heap = NULL;
	
	printf("~~~~~~~~~TestRemoveStruct~~~~~~~~~\n");
	
    heap = HeapCreate(&StructCmp, &param);
    status += ValCheck(NULL != heap, BOOL_TRUE,__LINE__);
	status += ValCheck(HeapPush(heap, &a), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &b), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &c), SUCCESS, __LINE__);
 	status += ValCheck(HeapPush(heap, &d), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &e), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &f), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &g), SUCCESS, __LINE__);
    status += ValCheck(HeapSize(heap), 7, __LINE__);

    PrintHeap(heap);
	
	printf("remove heapify up :\n");
	result = (st_int_t *)HeapRemove(heap, &e, &IsMatchStruct, NULL);
	status += ValCheck(result->elem, e.elem, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
   status += ValCheck(HeapSize(heap), 6, __LINE__);
	
	PrintHeap(heap);
	printf("!! manual compare to :\n");
	printf("%d %d %d %d %d %d \n\n", a.elem, g.elem, c.elem, d.elem, b.elem, f.elem);
	
	printf("remove root heapify down right:\n");
	result = (st_int_t *)HeapRemove(heap, &a, &IsMatchStruct, NULL);
	status += ValCheck(result->elem, a.elem, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 5, __LINE__);
	
	PrintHeap(heap);
	printf("!! manual compare to :\n");
	printf("%d %d %d %d %d \n\n", c.elem, g.elem, f.elem, d.elem, b.elem);
	
	printf("remove last:\n");
	result = (st_int_t *)HeapRemove(heap, &b, &IsMatchStruct, NULL);
	status += ValCheck(result->elem, b.elem, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 4, __LINE__);
	
	PrintHeap(heap);
	printf("!! manual compare to :\n");
	printf("%d %d %d %d \n\n", c.elem, g.elem, f.elem, d.elem);
	
	status += ValCheck(HeapPush(heap, &b), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &h), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &i), SUCCESS, __LINE__);
	status += ValCheck(HeapSize(heap), 7, __LINE__);
	
	printf("remove root heapify down left:\n");
	result = (st_int_t *)HeapRemove(heap, &c, &IsMatchStruct, NULL);
	status += ValCheck(result->elem, c.elem, __LINE__);
    status += ValCheck(HeapIsEmpty(heap), BOOL_FALSE, __LINE__);
    status += ValCheck(HeapSize(heap), 6, __LINE__);
	
	PrintHeap(heap);
	printf("!! manual compare to :\n");
	printf("%d %d %d %d %d %d\n\n", f.elem, g.elem, h.elem, d.elem, b.elem, i.elem);
	
	
    HeapDestroy(heap);
    heap = NULL;
    
    return status;
}

static int PeekPopTestStruct()
{
    int status = 0;
    int param = 2;
    st_int_t a = {101};
    st_int_t b = {30};
    st_int_t c = {40};
	st_int_t d = {18};
    st_int_t e = {19};
	st_int_t *result = NULL;
    
	heap_t *heap = NULL;
	
	printf("~~~~~~~~~PeekPopTestStruct~~~~~~~~~\n");
	
	heap = HeapCreate(&StructCmp, &param);
    status += ValCheck(NULL != heap, BOOL_TRUE,__LINE__);
	status += ValCheck(HeapPush(heap, &a), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &b), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &c), SUCCESS, __LINE__);
 	status += ValCheck(HeapPush(heap, &d), SUCCESS, __LINE__);
	status += ValCheck(HeapPush(heap, &e), SUCCESS, __LINE__);
    status += ValCheck(HeapSize(heap), 5, __LINE__);
	
	result = HeapPeek(heap);
	status += ValCheck(result->elem, a.elem, __LINE__);
	
	result = HeapPop(heap);
	status += ValCheck(result->elem, a.elem, __LINE__);
	
	result = HeapPeek(heap);
	status += ValCheck(result->elem, c.elem, __LINE__);
	
	result = HeapPop(heap);
	status += ValCheck(result->elem, c.elem, __LINE__);
	
	result = HeapPeek(heap);
	status += ValCheck(result->elem, b.elem, __LINE__);
	
	result = HeapPop(heap);
	status += ValCheck(result->elem, b.elem, __LINE__);
	
	result = HeapPeek(heap);
	status += ValCheck(result->elem, e.elem, __LINE__);
	
	result = HeapPop(heap);
	status += ValCheck(result->elem, e.elem, __LINE__);
	
	result = HeapPeek(heap);
	status += ValCheck(result->elem, d.elem, __LINE__);
	
	status += ValCheck(HeapSize(heap), 1, __LINE__);
	result = HeapPop(heap);
	status += ValCheck(result->elem, d.elem, __LINE__);
	
	status += ValCheck(HeapSize(heap), 0, __LINE__);
	status += ValCheck(HeapIsEmpty(heap), BOOL_TRUE, __LINE__);
	
    HeapDestroy(heap);
    heap = NULL;

    return status;
}
