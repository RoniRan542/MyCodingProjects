/***************************************************************
*Name : Ran Aharon Cohen	 									 *
*Reviewar:  														 *
*Date:  03/20/22													 *												 
*Description : 														 *
**********************************************************************/
#include <stdio.h> /* for printf */

#include "dll.h"

#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

int CreateDestroyTest(void);
int InsertRemoveIsEqualeTest(void);
int TestInt(const char *str, int expected, int result);
int PushFrontBackTest(void);
int FindMultyFindTest(void);
int ForEachTest(void);
int SpliceTest(void);
int IsMatch(const void *data, void *parameter);
int AddNum(void *data, void *parameter);
static void PrintList(dll_list_t *list);

int main()
{
   
	printf("----------------Test for Create Destroy ----------------\n");
    RUNTEST(CreateDestroyTest());
    printf("----------------Test for Insert Remove Is Equale----------------\n");
    RUNTEST(InsertRemoveIsEqualeTest());
    printf("----------------Test for Push Pop And Set Data----------------\n");
    RUNTEST(PushFrontBackTest());
    printf("----------------Test for Find and MultyFind----------------\n");
    RUNTEST(FindMultyFindTest());
    printf("----------------Test for For Each----------------\n");
    RUNTEST(ForEachTest());
    printf("----------------Test for Splice----------------\n");
    RUNTEST(SpliceTest());
    
    /* 
    printf("----------------Test for Is Empty Count----------------\n");
    RUNTEST(IsEmptyCountTest());
    printf("----------------Test for Prev Next----------------\n");
    RUNTEST(PrevNextTest());
    printf("----------------Test for Insert Get Set Data----------------\n");
    RUNTEST(InsertGetSetDataTest());
    printf("----------------Test for Push Pop----------------\n");
    RUNTEST(PushPopEqualTest());*/
    return 0;
}


int IsMatch(const void *data, void *parameter)
{
	return (*(int*)data == *(int*)parameter);
}

int ActionAdd(void *data, void *parameter)
{
	*(int *)data += *(int *)parameter;
	return 0;
}

static void PrintList(dll_list_t *list)
{
	if(NULL != DLLNext(DLLBegin(list)))
	{
	
	
	dll_iterator_t iter = NULL;
	iter = DLLBegin(list);
	while(DLLNext(iter) != DLLEnd(list))
	{
		printf("(%d)->",*(int *)DLLGetData(iter));
		iter = DLLNext(iter);
	}
	printf("(%d)\n",*(int *)DLLGetData(iter));
	}
}

int CreateDestroyTest(void)
{
	int result = 0;

	dll_list_t *list = DLLCreate();
	result += TestInt("IsEmpty", 1 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , DLLCount(list));
	result = 0;
	RUNTEST(result);
	DLLDestroy(list);
	return result;

}

int InsertRemoveIsEqualeTest(void)
{
	int data[6] = {1,2,3,4,5,6};
	int result = 0;
	dll_iterator_t iter = NULL;
	dll_iterator_t another_iter = NULL;
	dll_list_t *list = DLLCreate();
	
	result += TestInt("IsEmpty", 1 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 1, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[0])));
	RUNTEST(result);
	result = 0;
	result += TestInt("IsEmpty", 0 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 2, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[1])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 3, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[2])));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 3 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 4, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[3])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 5, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[4])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 6, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[5])));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 6 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	PrintList(list);
	iter = DLLNext(DLLBegin(list));
	another_iter = DLLNext(DLLBegin(list));
	result += TestInt("Is Equale" , 1, DLLIsIterEqual(iter,another_iter));
	RUNTEST(result);
	result = 0;
	result += TestInt("Remove" , 4, *(int *)DLLGetData(DLLRemove(iter)));
	RUNTEST(result);
	result = 0;
	iter = DLLPrev(DLLEnd(list));
	result += TestInt("Is Equale" , 0, DLLIsIterEqual(iter,another_iter));
	RUNTEST(result);
	result = 0;
	printf("\n%d\n",*(int *)DLLGetData(iter));
	DLLRemove(iter);
	iter = DLLPrev(DLLEnd(list));
	printf("\n%d\n",*(int *)DLLGetData(iter));
	DLLRemove(iter);
	result += TestInt("\nListCount" , 3 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	PrintList(list);
	DLLDestroy(list);
	return result;

}


int PushFrontBackTest(void)
{
	int data[7] = {10,20,30,40,50,60,70};
	int result = 0;
	dll_iterator_t iter = NULL;
	dll_list_t *list = DLLCreate();
	result += TestInt("IsEmpty", 1 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 10, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[0])));
	RUNTEST(result);
	result = 0;
	result += TestInt("IsEmpty", 0 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 20, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[1])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 30, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[2])));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 3 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	PrintList(list);
	DLLPushFront(list,&data[3]);
	PrintList(list);
	DLLPushFront(list,&data[4]);
	PrintList(list);
	DLLPushBack(list,&data[5]);
	PrintList(list);
	DLLPushBack(list,&data[6]);
	PrintList(list);
	iter = DLLBegin(list);
	DLLSetData(iter,&data[0]);
	iter = DLLNext(iter);
	DLLSetData(iter,&data[1]);
	iter = DLLNext(iter);
	DLLSetData(iter,&data[2]);
	iter = DLLNext(iter);
	DLLSetData(iter,&data[3]);
	iter = DLLNext(iter);
	DLLSetData(iter,&data[4]);
	PrintList(list);
	DLLPopFront(list);
	DLLPopFront(list);
	DLLPopBack(list);
	DLLPopBack(list);
	PrintList(list);
	DLLDestroy(list);
	return result;

}

int FindMultyFindTest(void)
{
	int data[8] = {10,20,30,40,50,60,70,80};
	int result = 0;
	dll_iterator_t from = NULL;
	dll_iterator_t to = NULL;
	is_match_func_t find_func = IsMatch;
	dll_list_t *list = DLLCreate();
	dll_list_t *list2 = DLLCreate();
	result += TestInt("IsEmpty", 1 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 10, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[0])));
	RUNTEST(result);
	result = 0;
	result += TestInt("IsEmpty", 0 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 20, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[1])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 30, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[2])));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 3 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	DLLPushFront(list,&data[3]);
	PrintList(list);
	DLLPushFront(list,&data[4]);
	PrintList(list);
	DLLPushFront(list,&data[5]);
	PrintList(list);
	DLLPushFront(list,&data[6]);
	PrintList(list);
	
	result += TestInt("ListCount" , 7 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	from = DLLBegin(list);
	to = DLLPrev(DLLEnd(list));
	printf("\n%d\n",*(int *)DLLGetData(DLLFindMatch(find_func, &data[2], from, to)));
	result += TestInt("Find Match" , 30, *(int *)DLLGetData(DLLFindMatch(find_func, &data[2], from, to)));
	RUNTEST(result);
	printf("\n%d\n",*(int *)DLLGetData(DLLFindMatch(find_func, &data[7], from, to)));
	result += TestInt("Find Match" , 10, *(int *)DLLGetData(DLLFindMatch(find_func, &data[7], from, to)));
	RUNTEST(result);
	result = 0;
	result += TestInt("Multy Find" , 0, DLLMultiFind(find_func, &data[7], from, to, list2));
	RUNTEST(result);
	result = 0;
	PrintList(list2);
	result += TestInt("Multy Find" , 0, DLLMultiFind(find_func, &data[4], from, to, list2));
	PrintList(list2);
	RUNTEST(result);
	result = 0;
	
	PrintList(list);
	
	DLLDestroy(list);
	DLLDestroy(list2);
	return result;
}

int ForEachTest(void)
{
	int data[8] = {10,20,30,40,50,60,70,80};
	int result = 0;
	dll_iterator_t from = NULL;
	dll_iterator_t to = NULL;
	action_func_t action_func = &ActionAdd;
	dll_list_t *list = DLLCreate();
	result += TestInt("ListCount" , 0 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 10, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[0])));
	RUNTEST(result);
	result = 0;
	result += TestInt("IsEmpty", 0 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 20, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[1])));
	RUNTEST(result);
	result = 0;
	DLLPushFront(list,&data[2]);
	DLLPushFront(list,&data[3]);
	DLLPushFront(list,&data[4]);
	DLLPushFront(list,&data[5]);
	PrintList(list);
	from = DLLBegin(list);
	to = DLLEnd(list);
	result += TestInt("For Each" , 0, DLLForEach(action_func, &data[0], from, to));
	RUNTEST(result);
	PrintList(list);
	result += TestInt("For Each" , 0, DLLForEach(action_func, &data[0], from, to));
	RUNTEST(result);
	result = 0;
	PrintList(list);
	
	DLLDestroy(list);
	return result;
}

int SpliceTest(void)
{
	int data[8] = {10,20,30,40,50,60,70,80};
	int result = 0;
	dll_iterator_t from = NULL;
	dll_iterator_t to = NULL;
	dll_iterator_t dest = NULL;
	dll_list_t *list = DLLCreate();
	dll_list_t *list2 = DLLCreate();
	result += TestInt("IsEmpty", 1 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 10, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[0])));
	RUNTEST(result);
	result = 0;
	result += TestInt("IsEmpty", 0 , DLLIsEmpty(list));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 20, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[1])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert", 30, *(int *)DLLGetData(DLLInsertBefore(DLLBegin(list),&data[2])));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 3 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	DLLPushFront(list,&data[3]);
	PrintList(list);
	DLLPushFront(list,&data[4]);
	PrintList(list);
	DLLPushFront(list,&data[5]);
	PrintList(list);
	DLLPushFront(list,&data[6]);
	PrintList(list);
	
	DLLPushFront(list2,&data[0]);
	result += TestInt("ListCount" , 7 , DLLCount(list));
	RUNTEST(result);
	result = 0;
	dest = DLLBegin(list2);
	
	from = DLLBegin(list);
	to = DLLNext(DLLNext(from));
	printf("%d\n",*(int *)DLLGetData(dest));
	printf("%d\n",*(int *)DLLGetData(from));
	printf("%d\n",*(int *)DLLGetData(to));
	PrintList(list);
	PrintList(list2);
	result += TestInt("Splice" , 60, *(int *)DLLGetData(DLLSplice(dest,from, to)));
	RUNTEST(result);
	
	PrintList(list);
	PrintList(list2);
	DLLDestroy(list);
	DLLDestroy(list2);
	return result;
}
int TestInt(const char *str, int expected, int result)
{
    printf("%s\n" , str);
    (void)str;
    return !(expected == result);
}
 
