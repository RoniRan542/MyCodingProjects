/*Author: Ran Aharon Cohen
 Date: 28.04.22
 Reviewed By: Hamotal
 */
#include <stdio.h> /* printf */ 

#include "bst.h"

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
                printf("Test Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

int TestInt(int expected, int result);
int TestCreate(void);
int TestInsert(void);
int TestForEach(void);
int Cmp(const void *new_data, const void * old_data, void *parameter);
int ActionAdd(void *data, void *parameter);
int Print(void *data, void *param);

int main()
{
    int result = 0;
    printf("\n\n***************************************************************\n");
    printf("*              Test For Create Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestCreate();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
   	printf("\n\n***************************************************************\n");
    printf("*              Test For Insert Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestInsert();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
   	printf("\n\n***************************************************************\n");
    printf("*              Test For ForEach Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestForEach();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
    return 0;
}

int TestCreate(void)
{
	int result = 0;
	void *param = NULL;
	
	bst_t *bst = BSTCreate(Cmp, &param); 
	if(bst == NULL)
	{
		printf("Naknic\n");
	}
	printf("Check if empty:\n");
	result += TestInt(1, BSTIsEmpty(bst));
	
	RUNTEST(result);
	
	BSTDestroy(bst);
	
	return result;
}

int TestInsert(void)
{
	int result = 0;
	void *param = NULL;
	int arr[] = {58, 19, 102, 99, 221, 120, 7 ,42, 82, 172};
	bst_t *bst = BSTCreate(Cmp, &param); 
	printf("Check if empty:\n");
	result += TestInt(1, BSTIsEmpty(bst));
	RUNTEST(result);
	printf("Check if count = 0:\n");
	result += TestInt(0, BSTCount(bst));
	RUNTEST(result);
	BSTInsert(bst, &arr[0]);															
	BSTInsert(bst, &arr[1]);
	BSTInsert(bst, &arr[2]);
	BSTInsert(bst, &arr[3]);
	BSTInsert(bst, &arr[4]);															
	BSTInsert(bst, &arr[5]);
	printf("Check if count = 6:\n");
	result += TestInt(6, BSTCount(bst));
	RUNTEST(result);
	BSTInsert(bst, &arr[6]);
	BSTInsert(bst, &arr[7]);
	BSTInsert(bst, &arr[8]);
	BSTInsert(bst, &arr[9]);
	printf("Check if count = 10:\n");
	result += TestInt(10, BSTCount(bst));
	RUNTEST(result);
	
	BSTDestroy(bst);
	
	return result;

}

int TestForEach(void)
{
	int result = 0;
	void *param = NULL;
	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;
	int arr[] = {58, 19, 102, 99, 221, 120, 7 ,42, 82, 172};
	bst_t *bst = BSTCreate(Cmp, &param); 
	printf("Check if empty:\n");
	result += TestInt(1, BSTIsEmpty(bst));
	RUNTEST(result);
	printf("Check if count = 0:\n");
	result += TestInt(0, BSTCount(bst));
	RUNTEST(result);
	BSTInsert(bst, &arr[0]);															
	BSTInsert(bst, &arr[1]);
	iter1 = BSTInsert(bst, &arr[2]);
	BSTInsert(bst, &arr[3]);
	BSTInsert(bst, &arr[4]);															
	BSTInsert(bst, &arr[5]);
	BSTInsert(bst, &arr[6]);
	BSTInsert(bst, &arr[7]);
	BSTInsert(bst, &arr[8]);
	BSTInsert(bst, &arr[9]);
	
	printf("Check if count = 10:\n");
	result += TestInt(10, BSTCount(bst));
	RUNTEST(result);
	BSTForeach(BSTBegin(bst), BSTEnd(bst), 
					Print, NULL);
	printf("\n");
	
	BSTRemove(iter1);
	BSTForeach(BSTBegin(bst), BSTEnd(bst), 
					Print, NULL);
	printf("\n");
	BSTRemove(BSTFind(bst,BSTBegin(bst), BSTEnd(bst),&arr[0]));
	BSTForeach(BSTBegin(bst), BSTEnd(bst), 
								Print, NULL);
	printf("\n");
	
	BSTDestroy(bst);
	
	return result;
}

int Cmp(const void *new_data, const void * old_data, void *parameter)
{
	(void)parameter;
	return (*(int *)new_data - *(int *)old_data); 
}

int TestInt(int expected, int result)
{
	return ((expected == result) ? 0 : 1);
}

int ActionAdd(void *data, void *parameter)
{
	*(int *)data += *(int *)parameter;
	
	return 0;
}

int Print(void *data, void *param)
{
	(void)param;
	printf("%d ~|", *(int *)data);
	
	return 0;
}
