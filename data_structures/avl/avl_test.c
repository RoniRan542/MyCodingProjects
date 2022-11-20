#include <stdio.h> /* printf */ 
#include "avl.h"
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
int TestWrite(void);
int TestCheck(void);
int Cmp(const void *data, const void * old_data, void *parameter);
int ActionAdd(void *data, void *parameter);
int Print(void *data, void *param);
int TestForEach(void);
int TestRemove(void);

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
    printf("*              Test For TestForEach Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestForEach();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   printf("\n\n***************************************************************\n");
    printf("*              Test For TestRemove Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestRemove();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
    return 0;
}

int TestCreate(void)
{
	int result = 0;
	void *param = NULL;
	int data = 6;
	int data2 = 12;
	int data3 = 8;
	int data4 = 14;
	int data5 = 4;
	int data6 = 10;
	int data7 = 2;
	int data8 = 11;
	int data9 = 9;
	
	avl_t *avl = NULL;
	avl = AVLCreate(&Cmp, &param);
	
	printf("Check if height is 0 and avl is empty:\n");
	result += TestInt(0, AVLHeight(avl));
	RUNTEST(result);
	result += TestInt(1, AVLIsEmpty(avl));
	RUNTEST(result);
	AVLInsert(avl, &data);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(1, AVLHeight(avl));
	RUNTEST(result);
	result += TestInt(0, AVLIsEmpty(avl));
	RUNTEST(result);
	AVLInsert(avl, &data2);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(2, AVLHeight(avl));
	RUNTEST(result);
	AVLInsert(avl, &data3);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(2, AVLHeight(avl));
	RUNTEST(result);
	AVLInsert(avl, &data4);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(3, AVLHeight(avl));
	RUNTEST(result);
	AVLInsert(avl, &data5);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(3, AVLHeight(avl));
	RUNTEST(result);
	AVLInsert(avl, &data6);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(3, AVLHeight(avl));
	RUNTEST(result);
	AVLInsert(avl, &data7);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(3, AVLHeight(avl));
	RUNTEST(result);
	AVLInsert(avl, &data8);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(4, AVLHeight(avl));
	RUNTEST(result);
	AVLInsert(avl, &data9);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(4, AVLHeight(avl));
	RUNTEST(result);
	
	AVLDestroy(avl);
	
	return result;
}
															
int TestForEach(void)
{
	int result = 0;
	void *param = NULL;
	int data = 6;
	int data2 = 12;
	int data3 = 8;
	int data4 = 14;
	int data5 = 4;
	int data6 = 10;
	int data7 = 2;											
	int data8 = 5;
	int data9 = 9;
	
	avl_t *avl = NULL;
	avl = AVLCreate(&Cmp, &param);
	
	printf("Check if height is 0 and avl is empty:\n");
	result += TestInt(0, AVLHeight(avl));
	RUNTEST(result);
	result += TestInt(1, AVLIsEmpty(avl));
	RUNTEST(result);
	AVLInsert(avl, &data);
	printf("height: %ld\n", AVLHeight(avl));
	result += TestInt(1, AVLHeight(avl));
	RUNTEST(result);
	result += TestInt(0, AVLIsEmpty(avl));
	RUNTEST(result);
	AVLInsert(avl, &data2);
	AVLForEach(avl, &Print, &param, 0);
	printf("\n\n");
	AVLInsert(avl, &data3);
	AVLForEach(avl, &Print, &param, 0);
	printf("\n\n");
	AVLInsert(avl, &data4);
	AVLForEach(avl, &Print, &param, 0);
	printf("\n\n");
	AVLInsert(avl, &data5);
	AVLForEach(avl, &Print, &param, 0);
	printf("\n\n");
	AVLInsert(avl, &data6);
	AVLForEach(avl, &Print, &param, 0);
	printf("\n\n");
	AVLInsert(avl, &data7);
	AVLForEach(avl, &Print, &param, 0);
	printf("\n\n");
	AVLInsert(avl, &data8);
	AVLForEach(avl, &Print, &param, 0);
	printf("\n\n");
	AVLInsert(avl, &data9);
	
	
	
	printf("\nCheck Preorder print:\n");
	AVLForEach(avl, &Print, &param, 0);
	printf("\nCheck Inorder print:\n");
	AVLForEach(avl, &Print, &param, 1);
	printf("\nCheck Postorder print:\n");
	AVLForEach(avl, &Print, &param, 2);
	
	AVLDestroy(avl);
	
	return result;
}

int TestRemove()
{
	int result = 0;
	int param = 1;
	avl_t *avl = AVLCreate(Cmp, &param);
	int tree[] = {97, 96, 100, 4, 95, 94, 93, 18, 200, 2, 187, 15, 17, 14, 1, 92, 99, 204,
				  186, 905, 374, 101, 190, 603, 605, 700, 750, 740};
	int not_found[] = {1000, 304, 5, 49, 102};
	
	result += TestInt(0, AVLInsert(avl, &tree[0]));
	result += TestInt(0, AVLInsert(avl, &tree[1]));
	result += TestInt(0, AVLInsert(avl, &tree[2]));
	result += TestInt(0, AVLInsert(avl, &tree[3]));
	result += TestInt(0, AVLInsert(avl, &tree[4]));
	result += TestInt(0, AVLInsert(avl, &tree[5]));
	result += TestInt(0, AVLInsert(avl, &tree[6]));
	result += TestInt(0, AVLInsert(avl, &tree[7]));
	result += TestInt(0, AVLInsert(avl, &tree[8]));
	result += TestInt(0, AVLInsert(avl, &tree[9]));
	result += TestInt(0, AVLInsert(avl, &tree[10]));
	result += TestInt(0, AVLInsert(avl, &tree[11]));
	RUNTEST(result);
	printf("\nCheck Preorder print:\n");
	AVLForEach(avl, &Print, &param, 0);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(97, *(int *)AVLFind(avl, &tree[0]));
	RUNTEST(result);
	result += TestInt(12, AVLCount(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[0]);
	result += TestInt(1, NULL == AVLFind(avl, &tree[0]));
	RUNTEST(result);
	printf("\nCheck Preorder print:\n");
	AVLForEach(avl, &Print, &param, 0);
	result += TestInt(11, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight 2: %ld\n",AVLHeight(avl));
	result += TestInt(4, AVLHeight(avl));
	printf("AVLHeight 3: %ld\n",AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[3]);/*remove 4*/
	result += TestInt(1, NULL == AVLFind(avl, &tree[3]));
	RUNTEST(result);
	result += TestInt(4, AVLHeight(avl));
	RUNTEST(result);
	printf("\nCheck Preorder print:\n");
	AVLForEach(avl, &Print, &param, 0);
	AVLRemove(avl, &tree[4]);/*remove 95*/
	result += TestInt(1, NULL == AVLFind(avl, &tree[4]));
	RUNTEST(result);
	result += TestInt(9, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight 4: %ld\n",AVLHeight(avl));
	result += TestInt(4, AVLHeight(avl));
	RUNTEST(result);
	printf("\nCheck Preorder print X:\n");
	AVLForEach(avl, &Print, &param, 0);
	AVLRemove(avl, &tree[8]);/*remove 200*/
	result += TestInt(1, NULL == AVLFind(avl, &tree[8]));
	RUNTEST(result);
	result += TestInt(8, AVLCount(avl));
	RUNTEST(result);
	printf("\nCheck Preorder print Y:\n");
	AVLForEach(avl, &Print, &param, 0);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(4, AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[11]);/*remove 15*/
	printf("\nCheck Preorder print Z:\n");
	AVLForEach(avl, &Print, &param, 0);
	result += TestInt(1, NULL == AVLFind(avl, &tree[11]));
	RUNTEST(result);
	result += TestInt(7, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(4, AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[1]);/*remove 96*/
	printf("\nCheck Preorder print ZA:\n");
	AVLForEach(avl, &Print, &param, 0);
	result += TestInt(1, NULL == AVLFind(avl, &tree[1]));
	RUNTEST(result);
	result += TestInt(6, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(4, AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[9]);/*remove 2*/
	printf("\nCheck Preorder print ZB:\n");
	AVLForEach(avl, &Print, &param, 0);
	result += TestInt(1, NULL == AVLFind(avl, &tree[9]));
	RUNTEST(result);
	result += TestInt(5, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(3, AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[5]);/*remove 94*/
	printf("\nCheck Preorder print ZC:\n");
	AVLForEach(avl, &Print, &param, 0);
	result += TestInt(1, NULL == AVLFind(avl, &tree[5]));
	RUNTEST(result);
	result += TestInt(4, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(3, AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[2]);/*remove 100*/
	printf("\nCheck Preorder print ZD:\n");
	AVLForEach(avl, &Print, &param, 0);
	result += TestInt(1, NULL == AVLFind(avl, &tree[2]));
	RUNTEST(result);
	result += TestInt(3, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(2, AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[7]);
	result += TestInt(1, NULL == AVLFind(avl, &tree[7]));
	RUNTEST(result);
	result += TestInt(2, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(2, AVLHeight(avl));
	RUNTEST(result);
	AVLRemove(avl, &tree[6]);
	result += TestInt(1, NULL == AVLFind(avl, &tree[6]));
	RUNTEST(result);
	result += TestInt(1, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(1, AVLHeight(avl));
	RUNTEST(result);
	printf("\nCheck Preorder print:\n");
	AVLForEach(avl, &Print, &param, 0);
	AVLRemove(avl, &tree[10]);
	result += TestInt(1, NULL == AVLFind(avl, &tree[10]));
	RUNTEST(result);
	result += TestInt(0, AVLCount(avl));
	RUNTEST(result);
	printf("AVLHeight: %ld\n",AVLHeight(avl));
	result += TestInt(0, AVLHeight(avl));
	RUNTEST(result);
	

	AVLDestroy(avl);
	
	return result;
}

int Cmp(const void *data, const void * old_data, void *parameter)
{
	(void)parameter;
	return (*(int *)data - *(int *)old_data); 
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


