/*******************************************************************************
*Name : Ran Aharon Cohen			 							               *
*Reviewer:  															       *
*Date: 10.3.22																   *
********************************************************************************/
#include <stdlib.h>/* malloc */
#include <assert.h>/* asserts */

#include "queue.h"
#include "slinked.h"
enum
{
	SUCCESS = 0,
	FAILED
};


struct queue
{
	s_linked_list_t *list;
};

queue_t *QueueCreate()
{
	queue_t *queue = malloc(sizeof(queue_t));
	if(NULL == queue)
	{
		return NULL;
	}
	queue->list = SLinkedListCreate();
	if(NULL == queue->list)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	return queue;
}

void QueueDestroy(queue_t *queue)
{
	SLinkedListDestroy(queue->list);
	free(queue);
	queue = NULL;
}

int QueueIsEmpty(const queue_t *queue)
{
	return SLinkedListIsEmpty(queue->list);
}

size_t QueueGetSize(const queue_t *queue)
{
	return SLinkedListCount(queue->list);
}

void *QueuePeek(const queue_t *queue)
{
	return SLinkedListGetData(SLinkedListBegin(queue->list));
}

int QueueEnqueue(queue_t *queue , void *data)
{
	if(SLinkedListInsertBefore(SLinkedListEnd(queue->list), data) == SLinkedListEnd(queue->list))
	{
		return 1; /* FAILURE */
	}
	
	return 0; /* SUCCESS */
}

void QueueDequeue(queue_t *queue)
{
	SLinkedListRemove(SLinkedListBegin(queue->list));
}

queue_t *QueueAppend(queue_t *dest ,queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	dest->list = SLinkedListAppend(dest->list, src->list);
	free(src);
	return dest;
}


void PrintQueue(queue_t *queue)
{
	assert(NULL != queue);
	
	SLinkedListPrintList(queue->list);
}
