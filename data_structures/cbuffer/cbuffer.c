/*******************************************************************************
Name: Ran Aharon Cohen
Reviewer: Stav Ben Shushan
Pass Vlg: Yes
Date: 16/03/2022
File: Circular Buffer
Description: Implementation of the Circular Buffer using struct.  
*******************************************************************************/
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <unistd.h> /* ssize_t */
#include <string.h> /* memcpy */
#include <time.h> /* nano - sleep */

#include "../include/cbuffer.h" /* file's header */

#define R_POS (c_buffer->read_position)
#define W_POS (c_buffer->write_position)

struct circular_buffer
{
	ssize_t read_position; /* front */
	ssize_t write_position; /*rear */
	size_t capacity; /* max num of elements */
	char buffer[1];	/* felxible */
};

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *cbuf = NULL;
	
	assert(0 != capacity);
	
	cbuf = (c_buffer_t *)malloc(sizeof(c_buffer_t) + capacity);
	if(NULL == cbuf)
	{
		return NULL;
	}
	
	cbuf->read_position = -1;
	cbuf->write_position = -1;
	cbuf->capacity = capacity; 
	
	return cbuf; 
}

void CBufferDestroy(c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	free(c_buffer);
	c_buffer = NULL;
}

ssize_t CBufferRead(c_buffer_t *c_buffer, void *dest, size_t count)
{
	ssize_t bytes_read = 0;	
	char *runner = (char *)dest;
	size_t cap = 0;
	size_t free = 0;
	
	assert(NULL != c_buffer);
	assert(NULL != dest);
	cap = CBufferCapacity(c_buffer);
	free = CBufferFreeSpace(c_buffer);
	if(CBufferIsEmpty(c_buffer))
	{
		return 0;
	}
	
	if(count > cap - free)
	{
		count = cap - free;
	}
	
	if((R_POS + count) >= cap)
	{
		memcpy(runner, (c_buffer->buffer + R_POS), cap - R_POS);
		runner += cap - R_POS;
		count -= cap - R_POS;
		bytes_read += cap - R_POS;
		R_POS = 0;
	}

	memcpy(runner,(c_buffer->buffer + R_POS) , count);
	R_POS += count;
	bytes_read += count;
	
	if(R_POS == W_POS)
	{
		R_POS = -1;
		W_POS = -1;
	}
	
	return bytes_read;
}

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *src, size_t count)
{
	ssize_t bytes_written = 0;	
	size_t free = 0;
	char *runner = (char *)src;
	size_t cap = 0;
	
	assert(NULL != c_buffer);
	assert(NULL != src);
	
	free = CBufferFreeSpace(c_buffer);
	cap = CBufferCapacity(c_buffer);
	
	if(CBufferIsEmpty(c_buffer))
	{
		R_POS = 0;
		W_POS = 0;
	}
	
	if(count > free)
	{
		count = free;
	}
	
	if(W_POS + count >= cap) 
	{
		memcpy((c_buffer->buffer + W_POS), runner, cap - W_POS);	
		runner += cap - W_POS;
		count -= cap - W_POS;
		bytes_written += cap - W_POS;
		W_POS = 0;
	}
	
	memcpy((c_buffer->buffer + W_POS), runner, count);
	W_POS += count;
	bytes_written += count;

	return bytes_written;
}

int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	return (-1 == R_POS);
}

size_t CBufferCapacity(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);
	
	return c_buffer->capacity;
}

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	size_t cap = 0;
	
	assert(NULL != c_buffer);
	cap = CBufferCapacity(c_buffer);
	
	if(CBufferIsEmpty(c_buffer))
	{
		return cap;
	}
	
	if( R_POS >= W_POS)
	{
		return R_POS - W_POS;
	}
	
	return  cap - (W_POS - R_POS);
}
