/*****************************************************************************
*Name: Ran Aharon Cohen												 		 *
*Reviewar:	Asaf									 			                 * 
*Date: 04/04/22													 			 *
*fsa.c													 		     	 *
******************************************************************************/

#include <assert.h>  /* for asserssions*/
#include <stddef.h>  /* for size_t and NULL*/

#include "fsa.h"  /* Fixed Size Allocator header*/

#define WORD_SIZE (sizeof(size_t))
#define FSA_SIZE (sizeof(fsa_t))
#define ALING_WORD_SIZE (sizeof(size_t) - 1)


struct fsa
{
	size_t offset;
};

size_t AlignBlockSize(size_t block_size);

size_t FSAReqPoolSize(size_t nblocks, size_t block_size)
{
	assert(0 != nblocks);
	assert(0 != block_size);
	
	block_size = AlignBlockSize(block_size);
	
	return FSA_SIZE + (nblocks * block_size);
}

size_t AlignBlockSize(size_t block_size)
{
	block_size += ALING_WORD_SIZE;
	
	return block_size & ~ ALING_WORD_SIZE;
}

fsa_t *FSAInit(void *mem_pool, size_t nblocks, size_t block_size)
{
	size_t i = 0;
	fsa_t *fsa_pool = NULL;
	char *runner = NULL;
	
	assert(NULL != mem_pool);
	
	fsa_pool = (fsa_t *)mem_pool;
	fsa_pool->offset = (size_t)FSA_SIZE;
	block_size = AlignBlockSize(block_size);
	
	runner = (char *)fsa_pool + FSA_SIZE;
	
	for(i = 1; i < nblocks; ++i)
	{
		*(size_t *)runner = FSA_SIZE + (i * block_size);
		runner += block_size;
	}
	*(size_t *)runner = 0;
	
	return fsa_pool;
}

void *FSAAlloc(fsa_t *pool)
{
	char *block = NULL;
	
	assert(NULL != pool);
	
	block = (char *)pool + pool->offset;
	pool->offset = *(size_t *)block; 
	*block = 0;
	return (void *)block;
}

void FSAFree(fsa_t *pool, void *block)
{
	assert(NULL != pool);
	assert(NULL != block);
	
	*(size_t *)block = pool->offset;
	pool->offset =  (char *)block - (char *)pool;
}

size_t FSACountFreeBlocks(const fsa_t *pool)
{
	char *runner = NULL;
	size_t counter = 0;
	
	assert(NULL != pool);
	
	runner = (char *)pool;

	while(0 != *(size_t *)runner)
	{
		++counter;
		runner = (char *)pool + *(size_t *)runner;
	}
	
	return counter;
}

/* 
    NOTE FOR ME! PLEASE IGNORE: 

    HELP TO UNDERSTAND WHY USING CHAR POINTER INSTEAD OF SIZE_T POINTER:
  
    printf("diff: %ld\n\n", (char *)block - (char *)pool); 
    printf("diff: %ld\n\n", (size_t *)block - (size_t *)pool); 
    
    EXAMPLE 1 :
    
    char * block address: 0x55bfc7e2eb88
    char * pool address: 0x55bfc7e2eb80

    diff: 8

    size_t * block address: 0x55bfc7e2eb88
    size_t * pool address: 0x55bfc7e2eb80

    diff: 1
    
    EXAMPLE 2 :

    char * block address: 0x55bfc7e2ea80
    char * pool address: 0x55bfc7e2ea60

    diff: 32 (WHY 32? 20 IN HEXADECIMAL)

    size_t * block address: 0x55bfc7e2ea80
    size_t * pool address: 0x55bfc7e2ea60

    diff: 4
*/
