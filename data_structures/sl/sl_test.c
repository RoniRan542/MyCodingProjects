/***************************************************************
*Name : Ran Aharon Cohen	 							     		 *
*Reviewar: 🐕️ May Sohatchevzzki 🤯️										 *
*Date:  03/22/22													 *												 
*Description : 	sorted list 												 *
**********************************************************************/
#include <stdio.h> /* for printf */
#include <assert.h>/* assert*/

#include "sl.h" /* sorted list header*/

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
int FindTest(void);
int PopTest(void);
int FindIfTest(void);
int ForEachTest(void);
int MergeTest(void);
int ModParam(const void *data, void *param);
int ActionAdd(void *data, void *parameter);
int Cmp(const void *new_data, const void *old_data, void *parameter);
int TestInt(const char *str, int expected, int result);
static void PrintList(sl_t *sl);
static sl_iterator_t FindNthFromEol(sl_t *sl, size_t n);

int main()
{
	printf("----------------Test for Create Destroy ----------------\n");
    RUNTEST(CreateDestroyTest());
    printf("----------------Test Insert----------------\n");
    RUNTEST(InsertTest());
    printf("----------------Test Find----------------\n");
    RUNTEST(FindTest());
    printf("----------------Test Pop----------------\n");
    RUNTEST(PopTest());
    printf("----------------Test Find If----------------\n");
    RUNTEST(FindIfTest());
    printf("----------------Test For Each----------------\n");
    RUNTEST(ForEachTest());
    printf("----------------Test Merge----------------\n");
    RUNTEST(MergeTest());
    return 0;
}

int CreateDestroyTest()
{
	int result = 0;
	int param = 6; 
	sl_cmp_func_t cmp_func = &Cmp;
	sl_t *sl = SLCreate(cmp_func, &param);
	result += TestInt("IsEmpty", 1 , SLIsEmpty(sl));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 0 , SLCount(sl));
	result = 0;
	RUNTEST(result);
	
	SLDestroy(sl);
	
	return 0;
}

int InsertTest()
{
	int result = 0;
	int param = 6; 
	int ints[6] = {1,3,2,5,6,4}; 
	sl_cmp_func_t cmp_func = &Cmp;
	sl_t *sl = SLCreate(cmp_func, &param);
	result += TestInt("IsEmpty", 1 , SLIsEmpty(sl));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ",1,*(int *)SLGetData(SLInsert(sl, &ints[0])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert ",3,*(int *)SLGetData(SLInsert(sl, &ints[1])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Insert SLEnd",3,*(int *)SLGetData(SLPrev(SLEnd(sl))));
	RUNTEST(result);
	result = 0;
	PrintList(sl);
	SLInsert(sl, &ints[3]);
	SLInsert(sl, &ints[4]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[0]);
	result += TestInt("IsEmpty", 0 , SLIsEmpty(sl));
	RUNTEST(result);
	result = 0;
	result += TestInt("ListCount" , 7 , SLCount(sl));
	RUNTEST(result);
	result = 0;
	/*result += TestInt("try Remove dummy ",6,*(int *)SLGetData(SLRemove(SLEnd(sl))));
	RUNTEST(result);
	result = 0;*/
	result += TestInt("remove one before last ",6,*(int *)SLGetData(SLRemove(SLPrev(SLPrev(SLEnd(sl))))));
	RUNTEST(result);
	result = 0;
	PrintList(sl);
	SLDestroy(sl);

	return 0;
}


int FindTest()
{
	int result = 0;
	int param = 6; 
	int n = 1;
	int ints[6] = {1,3,2,5,6,4}; 
	sl_iterator_t from = NULL;
	sl_iterator_t to = NULL;
	sl_cmp_func_t cmp_func = &Cmp;
	sl_t *sl = SLCreate(cmp_func, &param);
	
	SLInsert(sl, &ints[2]);
	SLInsert(sl, &ints[3]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[4]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[0]);
	
	from = SLBegin(sl);
	to = SLPrev(SLEnd(sl));
	
	result += TestInt("ListCount" , 7 , SLCount(sl));
	RUNTEST(result);
	result = 0;
	
	result += TestInt("Find" , 6 , *(int *)SLGetData(SLFind(sl,from, to, &ints[4])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Find" , 5 , *(int *)SLGetData(SLFind(sl,from, to, &ints[3])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Find" , 2 , *(int *)SLGetData(SLFind(sl,from, to, &ints[2])));
	RUNTEST(result);
	result = 0;
	result += TestInt("Find" , 6 , *(int *)SLGetData(SLFind(sl,from, to, &result)));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)SLGetData(FindNthFromEol(sl, n)));
	result += TestInt("FindNthFromEol" , 5 , *(int *)SLGetData(FindNthFromEol(sl, n)));
	RUNTEST(result);
	PrintList(sl);
	SLDestroy(sl);

	return 0;
}

int PopTest()
{
	int result = 0;
	int param = 6; 
	int ints[6] = {1,3,2,5,6,4}; 

	sl_cmp_func_t cmp_func = &Cmp;
	sl_t *sl = SLCreate(cmp_func, &param);
	
	SLInsert(sl, &ints[2]);
	SLInsert(sl, &ints[3]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[4]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[0]);
	
	result += TestInt("ListCount" , 7 , SLCount(sl));
	RUNTEST(result);
	result = 0;
	PrintList(sl);
	result += TestInt("Pop Front" , 1 , *(int *)SLPopFront(sl));
	RUNTEST(result);
	result = 0;
	result += TestInt("Pop Front" , 2 , *(int *)SLPopFront(sl));
	RUNTEST(result);
	result = 0;
	printf("%d\n",*(int *)SLPopBack(sl));
	/*result += TestInt("Pop Back" , 6 , *(int *)SLPopBack(sl));
	RUNTEST(result);
	result = 0;*/
	result += TestInt("Pop Back" , 5 , *(int *)SLPopBack(sl));
	RUNTEST(result);
	result = 0;
	PrintList(sl);
	SLDestroy(sl);

	return 0;
}


int FindIfTest()
{
	int result = 0;
	int param = 6; 
	int ints[6] = {1,3,2,5,6,4}; 
	sl_iterator_t from = NULL;
	sl_iterator_t to = NULL;
	sl_cmp_func_t cmp_func = &Cmp;
	sl_is_match_func_t is_match = &ModParam;
	sl_t *sl = SLCreate(cmp_func, &param);
	
	SLInsert(sl, &ints[2]);
	SLInsert(sl, &ints[3]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[4]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[0]);
	
	from = SLBegin(sl);
	to = SLPrev(SLEnd(sl));
	
	result += TestInt("ListCount" , 7 , SLCount(sl));
	RUNTEST(result);
	result = 0;
	from = SLNext(from);
	to = SLEnd(sl);
	result += TestInt("SLFindIf" , 6 , *(int *)SLGetData(SLFindIf(is_match, &ints[1],from, to)));
	RUNTEST(result);
	result = 0;
	result += TestInt("SLFindIf" , 5 , *(int *)SLGetData(SLFindIf(is_match, &ints[3],from, to)));
	RUNTEST(result);
	result = 0;
	from = SLNext(from);
	result += TestInt("SLFindIf" , 4 , *(int *)SLGetData(SLFindIf(is_match, &ints[2],from, to)));
	RUNTEST(result);
	result = 0;
	result += TestInt("SLFindIf" , 4 , *(int *)SLGetData(SLFindIf(is_match, &ints[5],from, to)));
	RUNTEST(result);
	result = 0;
	
	PrintList(sl);
	SLDestroy(sl);

	return 0;
}


int ForEachTest()
{
	int result = 0;
	int param = 2; 
	int ints[] = {1,3,2,5,6,4,4,4}; 
	sl_iterator_t from = NULL;
	sl_iterator_t to = NULL;
	sl_cmp_func_t cmp_func = &Cmp;
	sl_action_func_t action_func = &ActionAdd;
	sl_t *sl = SLCreate(cmp_func, &param);
	
	SLInsert(sl, &ints[2]);
	SLInsert(sl, &ints[3]);
	SLInsert(sl, &ints[7]);
	SLInsert(sl, &ints[4]);
	SLInsert(sl, &ints[5]);
	SLInsert(sl, &ints[6]);
	SLInsert(sl, &ints[0]);
	
	from = SLBegin(sl);
	to = SLPrev(SLEnd(sl));
	
	result += TestInt("ListCount" , 7 , SLCount(sl));
	RUNTEST(result);
	result = 0;
	to = SLEnd(sl);
	PrintList(sl);
	SLForEach(action_func, &param,from, to);
	result += TestInt("SL For each" , 3 , *(int *)SLGetData(from));
	RUNTEST(result);
	result = 0;
	PrintList(sl);
	result += TestInt("SL For each" , 8 , *(int *)SLGetData(SLPrev(to)));
	RUNTEST(result);
	result = 0;
	SLForEach(action_func, &param,from, to);
	result += TestInt("SL For each" , 5 , *(int *)SLGetData(from));
	RUNTEST(result);
	result = 0;	
	result += TestInt("SL For each" , 10 , *(int *)SLGetData(SLPrev(to)));
	RUNTEST(result);
	result = 0;
	
	PrintList(sl);
	SLDestroy(sl);

	return 0;
}

int MergeTest()
{
	int result = 0;
	int param = 2; 
	int data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	sl_cmp_func_t cmp_func = &Cmp;
	sl_t *src = SLCreate(cmp_func, &param);
	sl_t *dest = SLCreate(cmp_func, &param);
	
	
	SLInsert(dest, &data[1]);
	SLInsert(dest, &data[1]);
	SLInsert(dest, &data[3]);	
	SLInsert(dest, &data[4]);
	SLInsert(dest, &data[5]);
	/* the dest SL is now:  1 1 3 4 5 d */
	PrintList(dest);
	
	SLInsert(src, &data[0]);
	SLInsert(src, &data[1]);
	SLInsert(src, &data[2]);
	SLInsert(src, &data[3]);	
	SLInsert(src, &data[4]);
	SLInsert(src, &data[5]);
	SLInsert(src, &data[5]);	
	SLInsert(src, &data[7]);
	/* the src SL is now: 0 1 2 3 4 5 5 7  d */
	PrintList(src);

	dest = SLMerge(dest, src);
	PrintList(dest);
	
	src = SLMerge(src, dest);
	PrintList(src);

	SLDestroy(dest);
	SLDestroy(src);

	return result;

}

int ActionAdd(void *data, void *parameter)
{
	*(int *)data += *(int *)parameter;
	
	return 0;
}

int ModParam(const void *data, void *param)
{
	return (0 == (*(int *)data % *(int *)param));
}

int Cmp(const void *new_data, const void * old_data, void *parameter)
{
	(void)parameter;
	return (*(int *)old_data - *(int *)new_data); 
}

int TestInt(const char *str, int expected, int result)
{
    printf("%s\n" , str);
    (void)str;
    return !(expected == result);
}

static sl_iterator_t FindNthFromEol(sl_t *sl, size_t n)
{
	sl_iterator_t runner1 = NULL;
	sl_iterator_t runner2 = NULL;
	assert(NULL != sl);
	
	runner1 = SLBegin(sl);
	runner2 = SLBegin(sl);
	while(0 < n--)
	{
		runner2 = SLNext(runner2);
	}
	
	while(SLNext(runner2) != SLEnd(sl))
	{
		runner1 = SLNext(runner1);
		runner2 = SLNext(runner2);
	}
	
	return runner1;
}

static void PrintList(sl_t *sl)
{
	if(NULL != SLNext(SLBegin(sl)))
	{
	sl_iterator_t iter = NULL;
	iter = SLBegin(sl);
	while(SLNext(iter) != SLEnd(sl))
	{
		printf("(%d)->",*(int *)SLGetData(iter));
		iter = SLNext(iter);
	}
	printf("(%d)\n",*(int *)SLGetData(iter));
	}
}
