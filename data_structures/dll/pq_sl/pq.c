#include <assert.h>/* assert */
#include <stdlib.h>/* malloc, free*/

#include "sl.h"  /* sorted list header*/
#include "pq.h" /* priority queue header*/

struct pq
{
	sl_t *list;
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
	
	pq->list = SLCreate(cmp_func, param);
	if(NULL == pq->list)
	{
		free(pq);
		pq = NULL;
		return NULL;
	} 
	
	return pq;
} 	

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	SLDestroy(pq->list);
	free(pq);
	pq = NULL;
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SLIsEmpty(pq->list);
}		

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SLCount(pq->list);
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return SLGetData(SLBegin(pq->list));
}

int PQEnqueue(pq_t *pq, void *new_data)
{
	assert(NULL != pq);
	assert(NULL != new_data);
	
	return SLIsIterEqual(SLInsert(pq->list, new_data),SLEnd(pq->list));
}

void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return SLPopFront(pq->list);
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
	void * keep = NULL;
	sl_iterator_t iter_find = NULL;
	
	assert(NULL != pq);
	assert(NULL != is_match);
	
	iter_find = SLFindIf(is_match, param, SLBegin(pq->list),SLEnd(pq->list));
	if(SLIsIterEqual(SLEnd(pq->list),iter_find))
	{
		return NULL;
	}
	
	keep = SLGetData(iter_find);
	SLRemove(iter_find);
	
	return keep;
}
