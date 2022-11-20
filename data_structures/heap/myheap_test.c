#include <stdio.h> /* printf */ 
#include <assert.h> /* assert */

#include "heap.h"

#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m\x1b[1m\x1b[7m\x1b[5m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m\x1b[1m\x1b[7m\x1b[5m");\
                printf("Test Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

int total_fails = 0;

enum status
{
	SUCCESS = 0,
	BOOL_FALSE = 0,
	FAIL = 1,
	BOOL_TRUE = 1
} status_t;

int TestCreateDestroy(void);
int TestPushAndHeapifyUp(void);
int TestPopAndHeapifyDown(void);
int CmpFuncInt(const void *new_data, const void *current_data, void *cmp_param);
int IsMatch(const void *data, const void *heap_data, void *param);
int ValCheckInt(int recieved_val, int expected_val, int line);
int ValCheckSizeT(size_t recieved_val, size_t expected_val, int line_test);
void PrintTotalFailes(void);
int TestRemove(void);

int main(void)
{
    TestCreateDestroy();
	TestPushAndHeapifyUp();
	PrintTotalFailes();
	TestPopAndHeapifyDown();
	TestRemove();
	
	return 0;
}

int TestCreateDestroy(void)
{
	int status = 0;
	int result = 0;
	heap_cmp_func_t h_cmp = &CmpFuncInt;
	heap_t *heap = NULL;
	
    printf("\n\n***************************************************************\n");
    printf("*              Test For Create Function                       *\n");
    printf("***************************************************************\n\n");
	
	heap = HeapCreate(h_cmp, NULL);
	
	result = ValCheckInt(NULL != heap, BOOL_TRUE, __LINE__);
	status += result;

	result = ValCheckInt(HeapIsEmpty(heap), BOOL_TRUE, __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 0, __LINE__);
	status += result;

   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(status);
	
	HeapDestroy(heap);
	
	return status;

}

int TestPushAndHeapifyUp(void)
{
	int status = 0;
	int result = 0;
	heap_cmp_func_t h_cmp = &CmpFuncInt;
	heap_t *heap = NULL;
	int values[] = {5,4,10,-10,17,8};
	
    printf("\n\n***************************************************************\n");
    printf("*           Test For Insert and HeapifyUp Function            *\n");
    printf("***************************************************************\n\n");
	
	heap = HeapCreate(h_cmp, NULL);
	
	result = ValCheckInt(NULL != heap, BOOL_TRUE, __LINE__);
	status += result;

	result = ValCheckInt(HeapIsEmpty(heap), BOOL_TRUE, __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[0]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[0], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 1, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[1]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[0], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 2, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[2]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[2], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 3, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[3]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[2], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 4, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[4]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[4], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 5, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[5]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[4], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 6, __LINE__);
	status += result;

	PrintHeap(heap);

   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(status);
	
	HeapDestroy(heap);
	
	return status;

}

int TestPopAndHeapifyDown(void)
{
	int status = 0;
	int result = 0;
	heap_cmp_func_t h_cmp = &CmpFuncInt;
	heap_t *heap = NULL;
	int values[] = {5,4,10,-10,17,8};
	
    printf("\n\n***************************************************************\n");
    printf("*           Test For Pop And HeapifyDown Function            *\n");
    printf("***************************************************************\n\n");
	
	heap = HeapCreate(h_cmp, NULL);
	
	result = ValCheckInt(NULL != heap, BOOL_TRUE, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[0]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[1]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[2]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[3]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[4]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[5]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[4], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 6, __LINE__);
	status += result;
	
	HeapPop(heap);
	
	result = ValCheckInt(*(int *)HeapPeek(heap), values[2], __LINE__);
	status += result;
	
	result = ValCheckSizeT(HeapSize(heap), 5, __LINE__);
	status += result;
	
	HeapPop(heap);
	
	result = ValCheckInt(*(int *)HeapPeek(heap), values[5], __LINE__);
	status += result;
	
	result = ValCheckSizeT(HeapSize(heap), 4, __LINE__);
	status += result;
	
	PrintHeap(heap);
	
	HeapPop(heap);
	
	result = ValCheckInt(*(int *)HeapPeek(heap), values[0], __LINE__);
	status += result;
	
	result = ValCheckSizeT(HeapSize(heap), 3, __LINE__);
	status += result;
	
	HeapPop(heap);
	
	result = ValCheckInt(*(int *)HeapPeek(heap), values[1], __LINE__);
	status += result;
	
	result = ValCheckSizeT(HeapSize(heap), 2, __LINE__);
	status += result;
	PrintHeap(heap);
   	printf("THE FINAL RESULT OF THE TEST: ");
   	
   	RUNTEST(status);
	
	HeapDestroy(heap);
	
	return status;
}

int TestRemove(void)
{
	int status = 0;
	int result = 0;
	heap_cmp_func_t h_cmp = &CmpFuncInt;
	heap_t *heap = NULL;
	int values[] = {5,4,10,-10,17,8};
	
    printf("\n\n***************************************************************\n");
    printf("*           Test For Remove Function            *\n");
    printf("***************************************************************\n\n");
	
	heap = HeapCreate(h_cmp, NULL);
	
	result = ValCheckInt(NULL != heap, BOOL_TRUE, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[0]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[1]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[2]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[3]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[4]), 0, __LINE__);
	status += result;

	result = ValCheckInt(HeapPush(heap, &values[5]), 0, __LINE__);
	status += result;

	result = ValCheckInt(*(int *)HeapPeek(heap), values[4], __LINE__);
	status += result;

	result = ValCheckSizeT(HeapSize(heap), 6, __LINE__);
	
	status += result;
	
	PrintHeap(heap);
   	
   	HeapRemove(heap, &values[3], &IsMatch, NULL);
   	
   	PrintHeap(heap);
   	
   	HeapRemove(heap, &values[5], &IsMatch, NULL);
   	
   	PrintHeap(heap);
   	
   	HeapRemove(heap, &values[2], &IsMatch, NULL);
   	
   	
   	HeapPop(heap);
   	
   	PrintHeap(heap);
   	
   	HeapRemove(heap, &values[1], &IsMatch, NULL);
   	
   	PrintHeap(heap);
   	printf("THE FINAL RESULT OF THE TEST: ");
   	
   	RUNTEST(status);
	
	HeapDestroy(heap);
	
	return status;
}

int CmpFuncInt(const void *new_data, const void *current_data, void *cmp_param)
{
	assert(NULL != new_data);
	assert(NULL != current_data);
	
	(void)cmp_param;
	
	return (*(int *)new_data - *(int *)current_data);
}

int IsMatch(const void *data, const void *heap_data, void *param)
{
	(void)param;
	
	return *(int *)data == *(int *)heap_data;
}

int ValCheckInt(int recieved_val, int expected_val, int line_test)
{
	if (recieved_val != expected_val)
	{
		printf("-----------------------FAIL line ");
		printf("\x1b[7m\x1b[1m%d\x1b[0m", line_test);
		printf("--------------------------\n");
		
		printf("got \x1b[1m%d\x1b[0m", recieved_val);
		printf(", when wanted \x1b[1m%d\x1b[0m\n", expected_val);

		++total_fails;
		
		return FAIL;
	}
	return SUCCESS;
}

int ValCheckSizeT(size_t recieved_val, size_t expected_val, int line_test)
{
	if (recieved_val != expected_val)
	{
		printf("-----------------------FAIL line ");
		printf("\x1b[7m\x1b[1m%d\x1b[0m", line_test);
		printf("--------------------------\n");
		
		printf("got \x1b[1m%lu\x1b[0m", recieved_val);
		printf(", when wanted \x1b[1m%lu\x1b[0m\n", expected_val);

		++total_fails;
		
		return FAIL;
	}
	return SUCCESS;
}

void PrintTotalFailes(void)
{
	if (0 < total_fails)
	{
		printf("\x1b[5m\x1b[31m");
		printf("*********************** Total Fails = ");
		printf("\x1b[4m%d\x1b[0m", total_fails);
		printf("\x1b[5m\x1b[31m");
		printf("*********************");
		printf("\x1b[0m\n");
	}

	else
	{
		printf("\x1b[5m\x1b[32m");
		printf("*************** NO FAILESSS!! TRILILI TRALALA! **************");
		printf("\x1b[0m\n");
	}
}

