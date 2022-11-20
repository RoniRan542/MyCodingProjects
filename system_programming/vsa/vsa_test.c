/*************************************************
*Name : Ran Aharon Cohen						 *
*Reviewar:	Nuriel	 	    			         *
*Date: 	09.04.22		            		 	 *
*Description :vsa - Variable Size Allocator	     *
**************************************************/
#include <stdio.h> /* printf */ 
#include <stdlib.h>  /* malloc, free */ 

#include "vsa.h"

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
int TestInit(void);
int TestAlloc(void);
int TestFree(void);

int main()
{
    int result = 0;
    printf("\n\n***************************************************************\n");
    printf("*              Test For Init Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestInit();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
    printf("\n\n***************************************************************\n");
    printf("*            Test For Alloc Function                 *\n");
    printf("***************************************************************\n\n");
    result = TestAlloc();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	printf("\n\n***************************************************************\n");
    printf("*            Test For Free Function                 *\n");
    printf("***************************************************************\n\n");
    result = TestFree();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
    return 0;
}

int TestInit(void)
{
	int result = 0;
	void *pool = (void *)malloc(130);
	vsa_t * my_vsa = VSAInit(pool, 130);
	
	printf("Check if capacity of free block is 120:\n");
	result += TestInt(120, VSALargestFreeBlock(my_vsa));
	RUNTEST(result);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	free(pool);
	pool = NULL;
	
	return result;
}


int TestAlloc(void)
{
	int result = 0;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *pool = (void *)malloc(130);
	vsa_t * my_vsa = VSAInit(pool, 130);
	
	printf("Check if capacity of free block is 120:\n");
	result += TestInt(120, VSALargestFreeBlock(my_vsa));
	RUNTEST(result);
	
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	block1 = VSAAlloc(my_vsa, 16);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	printf("Check if capacity of largest free block is 96:\n");
	result += TestInt(96, VSALargestFreeBlock(my_vsa));
	RUNTEST(result);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	block2 = VSAAlloc(my_vsa, 16);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	printf("Check if capacity of largest free block is 72:\n");
	result += TestInt(72, VSALargestFreeBlock(my_vsa));
	RUNTEST(result);
	block3 = VSAAlloc(my_vsa, 42);
	printf("Check if capacity of largest free block is 16:\n");
	result += TestInt(16, VSALargestFreeBlock(my_vsa));
	RUNTEST(result);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	
	free(pool);
	pool = NULL;
	
	return result; 
}


int TestFree(void)
{
	int result = 0;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	void *pool = malloc(130);
	vsa_t * my_vsa = VSAInit(pool, 130);
	
	printf("Check if capacity of free block is 120:\n");
	result += TestInt(120, VSALargestFreeBlock(my_vsa));
	RUNTEST(result);
	
	
	block1 = VSAAlloc(my_vsa, 16);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	
	block2 = VSAAlloc(my_vsa, 16);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	
	block3 = VSAAlloc(my_vsa, 16);
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	
	block4 = VSAAlloc(my_vsa, 16); 
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	
	block5 = VSAAlloc(my_vsa, 16); 
	printf("meta data 5 : %ld\n",*(size_t *)((char *)my_vsa + 96));
	printf("VSALargestFreeBlock:%ld\n",VSALargestFreeBlock(my_vsa));
	
	VSAFree(block1);
	
	printf("VSALargestFreeBlock 16? %ld\n",VSALargestFreeBlock(my_vsa));
	
	
	VSAFree(block2);
	printf("meta data 5 : %ld\n",*(size_t *)((char *)my_vsa + 96));
	printf("VSALargestFreeBlock 40? %ld\n",VSALargestFreeBlock(my_vsa));
	
	VSAFree(block3);
	printf("meta data 5 : %ld\n",*(size_t *)((char *)my_vsa + 96));
	printf("VSALargestFreeBlock 64? %ld\n",VSALargestFreeBlock(my_vsa));
	
	VSAFree(block4);
	printf("meta data 5 : %ld\n",*(size_t *)((char *)my_vsa + 96));
	printf("VSALargestFreeBlock 88? %ld\n",VSALargestFreeBlock(my_vsa));
	VSAFree(block5);
	
	printf("VSALargestFreeBlock 120? %ld\n",VSALargestFreeBlock(my_vsa));
	free(pool);
	pool = NULL;
	
	return result; 
}

int TestInt(int expected, int result)
{
	return ((expected == result) ? 0 : 1);
}
