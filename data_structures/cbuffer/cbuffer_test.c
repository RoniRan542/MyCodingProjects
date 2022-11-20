/*******************************************************************************
Name: Ran Aharon Cohen
Reviewer: 
Pass Vlg: 
Date: 16/03/2022
File: Circular Buffer
Description: Implementation of the Circular Buffer using struct.  
*******************************************************************************/
#include <stdio.h> /* printf */

#include "cbuffer.h" 


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
    printf("*            Test For Write and Read Function                    *\n");
    printf("***************************************************************\n\n");
    result = TestWrite();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	printf("\n\n***************************************************************\n");
    printf("*            Test For WRITE SRC Function                    *\n");
    printf("***************************************************************\n\n");
    result = TestCheck();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
    return 0;
}

int TestCreate(void)
{
	int result = 0;
	c_buffer_t *c_buffer = CBufferCreate(5);
	printf("Check if capacity is 5:\n");
	result += TestInt(5, CBufferCapacity(c_buffer));
	RUNTEST(result);
	printf("Check if the new c_buffer is empty:\n");
	result += TestInt(1, CBufferIsEmpty(c_buffer));
	RUNTEST(result);
	printf("Check if the free space is 5:\n");
	result += TestInt(5, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	
	CBufferDestroy(c_buffer);
	
	return result;
}

int TestCheck(void)
{
	int result = 0;
	const char *src = "ABCDEFG";
	char arr[50] = "";
	c_buffer_t *c_buffer = CBufferCreate(20);
	printf("Check if the new c_buffer is empty:\n");
	result += TestInt(1, CBufferIsEmpty(c_buffer));
	RUNTEST(result);
	printf("Check if the free space is 20:\n");
	result += TestInt(20, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the write return 7:\n");
	
	printf("\n\n%lu\n\n", CBufferWrite(c_buffer, src, 10));
	
	result += TestInt(10, CBufferWrite(c_buffer, src, 10));
	RUNTEST(result);
	
	CBufferDestroy(c_buffer);
	return result;
}

int TestWrite(void)
{
	int result = 0;
	const char *src = "ABCDEFG";
	char arr[50] = "";
	c_buffer_t *c_buffer = CBufferCreate(5);
	printf("Check if the new c_buffer is empty:\n");
	result += TestInt(1, CBufferIsEmpty(c_buffer));
	RUNTEST(result);
	printf("Check if the free space is 5:\n");
	result += TestInt(5, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the write return 3:\n");
	result += TestInt(3, CBufferWrite(c_buffer, src, 3));
	RUNTEST(result);
	printf("Check if the new c_buffer is not empty:\n");
	result += TestInt(0, CBufferIsEmpty(c_buffer));
	RUNTEST(result);
	printf("Check if the free space is 2:\n");
	result += TestInt(2, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the write return 2:\n");
	result += TestInt(2, CBufferWrite(c_buffer, src, 3));
	RUNTEST(result);
	printf("Check if the free space is 0:\n");
	result += TestInt(0, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the new c_buffer is not empty:\n");
	result += TestInt(0, CBufferIsEmpty(c_buffer));
	RUNTEST(result);
	printf("Check if the write of 3 return 0:\n");
	result += TestInt(0, CBufferWrite(c_buffer, src, 3));
	RUNTEST(result);
	
	
	/************************ Check for READ ************************/

	printf("Check if the read of 3 return 3:\n");
	result += TestInt(3, CBufferRead(c_buffer, arr, 3));
	RUNTEST(result);
	printf("Check if the free space is 3:\n");
	result += TestInt(3, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the read of 10 return 2:\n");
	result += TestInt(2, CBufferRead(c_buffer, arr, 10));
	RUNTEST(result);
	printf("Check if the new c_buffer is empty:\n");
	result += TestInt(1, CBufferIsEmpty(c_buffer));
	RUNTEST(result);
	printf("Check if the free space is 5:\n");
	result += TestInt(5, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the write return 5:\n");
	result += TestInt(5, CBufferWrite(c_buffer, src, 5));
	RUNTEST(result);
	printf("Check if the read of 3 return 3:\n");
	result += TestInt(3, CBufferRead(c_buffer, arr, 3));
	RUNTEST(result);
	printf("Check if the write of 5 return 3:\n");
	result += TestInt(3, CBufferWrite(c_buffer, src, 5));
	RUNTEST(result);
	printf("Check if the free space is 0:\n");
	result += TestInt(0, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the read of 4 return 4:\n");
	result += TestInt(4, CBufferRead(c_buffer, arr, 4));
	RUNTEST(result);
	printf("Check if the free space is 4:\n");
	result += TestInt(4, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	printf("Check if the write of 1 return 1:\n");
	result += TestInt(1, CBufferWrite(c_buffer, src, 1));
	RUNTEST(result);
	printf("Check if the write of 2 return 2:\n");
	result += TestInt(2, CBufferWrite(c_buffer, src, 2));
	RUNTEST(result);
	printf("Check if the free space is 1:\n");
	result += TestInt(1, CBufferFreeSpace(c_buffer));
	RUNTEST(result);
	
	CBufferDestroy(c_buffer);
	
	return result; 
}

int TestInt(int expected, int result)
{
	return ((expected == result) ? 0 : 1);
}
