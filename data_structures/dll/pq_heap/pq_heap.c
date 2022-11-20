#include <assert.h>/* assert */
#include <stdlib.h>/* malloc, free*/

#include "heap.h"  /* sorted list header*/
#include "pq_heap.h" /* priority queue header*/
#define FREE(ptr) free(ptr);\
                    ptr = NULL;

static int IsMatchWrapper(const void *to_remove, const void *heap_data, void *param);
static int PQIsMatch(const void *current_data, void *param);

enum status
{
    SUCCESS = 0,
    FAILURE
};

struct pq
{
	heap_t *heap;
};

pq_t *PQCreate(pq_cmp_func_t cmp_func, void *param)
{
	pq_t *pq = NULL;
	assert(NULL != cmp_func);
	
	pq = (pq_t *)malloc(sizeof(pq_t)); 
	if(NULL == pq)
	{
		return NULL;
	}
	
	pq->heap = HeapCreate(cmp_func, param);
	if(NULL == pq->heap)
	{
		FREE(pq);
		return NULL;
	} 
	
	return pq;
} 	

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	HeapDestroy(pq->heap);
	FREE(pq);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapIsEmpty(pq->heap);
}		

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapSize(pq->heap);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPeek(pq->heap);
}

int PQEnqueue(pq_t *pq, void *new_data)
{
	int status = 0;
	
	assert(NULL != pq);
	assert(NULL != new_data);
	
	status = HeapPush(pq->heap, new_data);
    if(SUCCESS != status)
    {
        PQErase(pq, new_data, PQIsMatch);
    }
    
	return status;
}

void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return HeapPop(pq->heap);
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while(!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pq_t *pq, void *param,  pq_is_match_t is_match)
{
	assert(NULL != pq);
	assert(NULL != is_match);

	return HeapRemove(pq->heap, &is_match, &IsMatchWrapper, param);
}

static int PQIsMatch(const void *current_data, void *param)
{
    return current_data == param;
}

static int IsMatchWrapper(const void *pq_func, const void *heap_data, void *param)
{
	return (*(pq_is_match_t *)pq_func)(heap_data, param);
}
