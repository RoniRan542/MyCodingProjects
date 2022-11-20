/*****************************************************************************
*Name: Ran Aharon Cohen												 			 *
*Reviewar:										 			 *
*Date: 04/04/22													 			 *
*fsa_test.c													 			 *
******************************************************************************/
#include <stdio.h> /* printf */ 
#include <stdlib.h>

#include "fsa.h"

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
int TestReq(void);
int TestInit(void);
int TestAlloc(void);
int TestFree(void);

int main()
{
    int result = 0;
    printf("\n\n***************************************************************\n");
    printf("*              Test For Req                        *\n");
    printf("***************************************************************\n\n");
    result = TestReq();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
   	printf("\n\n***************************************************************\n");
    printf("*            Test For Init             *\n");
    printf("***************************************************************\n\n");
    result = TestInit();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
   	printf("\n\n***************************************************************\n");
    printf("*            Test For Alloc            *\n");
    printf("***************************************************************\n\n");
    result = TestAlloc();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
   	printf("\n\n***************************************************************\n");
    printf("*            Test For Free            *\n");
    printf("***************************************************************\n\n");
    result = TestFree();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
 
    return 0;
}

int TestReq(void)
{
	int result = 0;
	size_t nblocks = 20;
	size_t block_size = 8;
	size_t block_size2 = 8;
	printf("Check if block_size is 168:\n");
	result += TestInt(168, FSAReqPoolSize(nblocks, block_size));
	RUNTEST(result);
	printf("Check if block_size2 is 168:\n");
	result += TestInt(168, FSAReqPoolSize(nblocks, block_size2));
	RUNTEST(result);
	
	return result;
}

int TestInit(void)
{
	int result = 0;
	size_t nblocks = 40;
	size_t block_size = 8;
	size_t actual_block_size = 8;
	size_t block = 1;
	size_t pool_size = 0;
	void *mem_pool = NULL;
	fsa_t *fsa_pool = NULL; 
	char *runner = NULL;
	
	
	pool_size = FSAReqPoolSize(nblocks, block_size);
	mem_pool = malloc(pool_size);
	if (NULL == mem_pool) {return 1;}
	fsa_pool = FSAInit(mem_pool, nblocks, block_size);
		
	runner = (char *)fsa_pool + 8;
	while(runner != ((char *)fsa_pool + 328))
	{
		printf("num in block %ld: %lu.\n", block, *(size_t *)runner);
        runner += actual_block_size;
        block++;

	}
	
	printf("counter of free blocks: %ld\n",FSACountFreeBlocks(fsa_pool));
	free(mem_pool);
	mem_pool = NULL;
	return result; 
}

int TestAlloc(void)
{
	int result = 0;
	size_t i = 0;
	size_t nblocks = 5;
	size_t block_size = 10;
	size_t actual_block_size = 16;
	size_t block = 1;
	size_t pool_size = 0;
	void *mem_pool = NULL;
	fsa_t *fsa_pool = NULL; 
	char *data[5] = {NULL};
	pool_size = FSAReqPoolSize(nblocks, block_size);
	mem_pool = malloc(pool_size);
	if (NULL == mem_pool) {return 1;}
	fsa_pool = FSAInit(mem_pool, nblocks, block_size);
	printf("counter of free blocks: %ld\n",FSACountFreeBlocks(fsa_pool));
	while(i < nblocks)
	{
		data[i] = (char *)FSAAlloc(fsa_pool);
		data[i] = "hello";
		++i;
	}
	printf("print data: %s\n",(char *)data[3]);
	printf("counter of free blocks: %ld\n",FSACountFreeBlocks(fsa_pool));
	
	free(mem_pool);
	mem_pool = NULL;
	return result; 
}

int TestFree(void)
{
	int result = 0;
	size_t i = 0;
	size_t nblocks = 5;
	size_t block_size = 10;
	size_t actual_block_size = 16;
	size_t block = 1;
	size_t pool_size = 0;
	void *mem_pool = NULL;
	fsa_t *fsa_pool = NULL; 
	void *data[5] = {NULL};
	pool_size = FSAReqPoolSize(nblocks, block_size);
	mem_pool = malloc(pool_size);
	if (NULL == mem_pool) {return 1;}
	fsa_pool = FSAInit(mem_pool, nblocks, block_size);
	
	while(i < nblocks)
	{
		data[i] = FSAAlloc(fsa_pool);
		data[i] = (void *)"Hello";
		++i;
	}
	
	
	result += TestInt(0, FSACountFreeBlocks(fsa_pool));
	RUNTEST(result);
	
	FSAFree(fsa_pool, &data[1]);
	
	result += TestInt(1, FSACountFreeBlocks(fsa_pool));
	RUNTEST(result);
	
	FSAFree(fsa_pool, &data[2]);
	
	result += TestInt(2, FSACountFreeBlocks(fsa_pool));
	RUNTEST(result);
	
	FSAFree(fsa_pool, &data[3]);
	
	result += TestInt(3, FSACountFreeBlocks(fsa_pool));
	RUNTEST(result);
	
	FSAFree(fsa_pool, &data[0]);
	
	result += TestInt(4, FSACountFreeBlocks(fsa_pool));
	RUNTEST(result);
	
	FSAFree(fsa_pool, &data[4]);
	
	result += TestInt(5, FSACountFreeBlocks(fsa_pool));
	RUNTEST(result);
	
	free(mem_pool);
	mem_pool = NULL;
	return result; 
}

int TestInt(int expected, int result)
{
	return ((expected == result) ? 0 : 1);
}
