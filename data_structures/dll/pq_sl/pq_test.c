/***************************************************************
*Name : Ran Aharon Cohen	 							     		 *
*Reviewar: 🐕️ May Sohatchevzzki 🤯️										 *
*Date:  03/22/22													 *												 
*Description : 	priority queue												 *
**********************************************************************/
#include <stdio.h> /* for printf */

#include "pq.h" /* sorted list header*/

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
int InsertTest(void);
int EraseTest(void);
/*int FindTest(void);
int PopTest(void);
int FindIfTest(void);
int ForEachTest(void);
int MergeTest(void);*/
static int IsMatch(const void *data, void *param);
/*static int ModParam(const void *data, void *param);
static int ActionAdd(void *data, void *parameter);*/
static int Cmp(const void *new_data, const void *old_data, void *parameter);
static int TestInt(const char *str, int expected, int result);


int main()
{
	printf("----------------Test for Create Destroy ----------------\n");
    RUNTEST(CreateDestroyTest());
    printf("----------------Test Insert----------------\n");
    RUNTEST(InsertTest());
    printf("----------------Test Erase----------------\n");
    RUNTEST(EraseTest());
    /*printf("----------------Test Find----------------\n");
    RUNTEST(FindTest());
    printf("----------------Test Pop----------------\n");
    RUNTEST(PopTest());
    printf("----------------Test Find If----------------\n");
    RUNTEST(FindIfTest());
    printf("----------------Test For Each----------------\n");
    RUNTEST(ForEachTest());
    printf("----------------Test Merge----------------\n");
    RUNTEST(MergeTest());*/
    return 0;
}


int CreateDestroyTest()
{
	int result = 0;
	int param = 2; 
	pq_cmp_func_t cmp_func = &Cmp;
	pq_t *pq = PQCreate(cmp_func, &param); 
	result += TestInt("IsEmpty", 1 , PQIsEmpty(pq));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , PQSize(pq));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	
	PQDestroy(pq);
	
	return result;
}

int InsertTest()
{
	int result = 0;
	int param = 2; 
	int ints[6] = {1,3,2,5,6,4}; 
	pq_cmp_func_t cmp_func = &Cmp;                             
	pq_t *pq = PQCreate(cmp_func, &param); 
	result += TestInt("IsEmpty", 1 , PQIsEmpty(pq));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , PQSize(pq));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[1]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[0]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[1]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[0]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[1]));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[0]));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[1]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[4]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Remove ", 6, *(int *)PQDequeue(pq));
	RUNTEST(result);
	result = 0;
	result += TestInt("IsEmpty", 0 , PQIsEmpty(pq));
	RUNTEST(result);
	result = 0;
	PQClear(pq);
	result += TestInt("IsEmpty", 1 , PQIsEmpty(pq));
	RUNTEST(result);
	result = 0;
	
	printf("%d\n",*(int *)PQPeek(pq));
	
	PQDestroy(pq);
	

	return 0;
}

int EraseTest()
{
	int result = 0;
	int param = 5; 
	int ints[6] = {1,2,3,4,5,6}; 
	pq_cmp_func_t cmp_func = &Cmp;
	pq_is_match_t is_match = &IsMatch;
	pq_t *pq = PQCreate(cmp_func, &param); 
	result += TestInt("IsEmpty", 1 , PQIsEmpty(pq));
	RUNTEST(result);
	result = 0;
	printf("%ld\n",PQSize(pq));
	result += TestInt("ListCount" , 0 , PQSize(pq));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[0]));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[1]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[2]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[3]));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[4]));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	result += TestInt("Insert ", 0, PQEnqueue(pq, &ints[5]));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 6, PQSize(pq));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	result += TestInt("Erase ", 4, *(int *)PQErase(pq, &param, is_match));
	RUNTEST(result);
	result = 0;
	result += TestInt("Erase ", 3, *(int *)PQErase(pq, &param, is_match));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)PQPeek(pq));
	printf("%ld\n",PQSize(pq));
	result += TestInt("ListCount" , 4, PQSize(pq));
	RUNTEST(result);
	result = 0;
	
	PQDestroy(pq);
	
	return result;
}

static int IsMatch(const void *data, void *param)
{
	return *(int *)data < *(int *)param;
}



static int Cmp(const void *new_data, const void * old_data, void *parameter)
{
	(void)parameter;
	return (*(int *)new_data - *(int *)old_data); 
}

static int TestInt(const char *str, int expected, int result)
{
    printf("%s\n" , str);
    (void)str;
    return !(expected == result);
}
/*
static int ModParam(const void *data, void *param)
{
	return (0 == (*(int *)data % *(int *)param));
}

static int ActionAdd(void *data, void *parameter)
{
	*(int *)data += *(int *)parameter;
	
	return 0;
}
*/
