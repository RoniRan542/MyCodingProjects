#include <stdlib.h>/* malloc , free*/
#include <assert.h>/* assert */

#include "dll.h"

static int IsHead(dll_iterator_t iter);
static int CounterCompare(int counter, int compare);
static void ConnectIters(dll_iterator_t iter1, dll_iterator_t iter2);
static dll_iterator_t ReturnNULLNode (dll_iterator_t where);

typedef struct DLL_node dll_node_t;

struct DLL_node
{
    void *data;
    dll_node_t *next;
    dll_node_t *prev;
};

struct DLL_list 
{
    dll_node_t *head;
    dll_node_t *tail;
};

enum status
{
	SUCCESS,
	FAILURE
};

dll_list_t *DLLCreate(void)
{
	dll_node_t *dummy_node = NULL;
	dll_list_t *list = (dll_list_t *)malloc(sizeof(dll_list_t));
	if(NULL == list)
	{
		return NULL;
	}
	
	dummy_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	if(NULL == dummy_node)
	{
		free(list);
		list = NULL;
		return NULL;
	}
	
	list->head = dummy_node;
	list->tail = dummy_node;
	
	dummy_node->next = NULL;
	dummy_node->prev = dummy_node;
	dummy_node->data = list;
	
	return list;
}

void DLLDestroy(dll_list_t *list)
{
	dll_iterator_t iter = NULL;
	assert(NULL != list);
	iter = list->head;
	
	while(!DLLIsEmpty(list))
	{
		iter = DLLRemove(iter);
	}
	
	free(iter);
	list->head = NULL;
	free(list);
	list = NULL;
}


int DLLIsEmpty(const dll_list_t *list)
{
	assert(NULL != list);
	
	return NULL == (list->head)->next;
}

dll_iterator_t DLLNext(const dll_iterator_t iter)
{
	assert(NULL != iter);

	return iter->next;
}


dll_iterator_t DLLPrev(const dll_iterator_t iter)
{
	assert(NULL != iter);

	return iter->prev;
}

void *DLLGetData(const dll_iterator_t where)
{
	assert(NULL != where);
	
	return where->data;/* If the iter is end of list undefined behavior occures*/
}

void DLLSetData(dll_iterator_t where, void *new_data)
{
	assert(NULL != where);
	
	if(NULL != DLLNext(where))
	{
		where->data = new_data;
	}
}

size_t DLLCount(const dll_list_t *list)
{
	size_t count = 0;
	dll_iterator_t iter = NULL;
	assert(NULL != list);
	iter = list->head;
	
	while(!DLLIsIterEqual(DLLEnd(list),iter))
	{
		iter = DLLNext(iter);
		++count;
	}
	
	return count;
}

int DLLIsIterEqual(const dll_iterator_t iter1, const dll_iterator_t iter2)
{	
	return iter1 == iter2;
}

dll_iterator_t DLLBegin(const dll_list_t *list)
{
	assert(NULL != list);
	
	return list->head;
}

dll_iterator_t DLLEnd(const dll_list_t *list)
{
	assert(NULL != list);
	
	return list->tail;
}

dll_iterator_t DLLRemove(dll_iterator_t iter)/*return next iterator*/
{
	dll_iterator_t next_node = NULL;
	dll_iterator_t prev_node = NULL;
	assert(NULL != iter);
	
	if(NULL == DLLNext(iter))
	{
		return iter->prev;
	}
	
	next_node = iter->next;
	prev_node = iter->prev;
	next_node->prev = prev_node;

	if(IsHead(iter))
	{
		((dll_list_t *)DLLGetData(DLLPrev(iter)))->head = next_node;
	}
	else
	{
		prev_node->next = next_node;
	}
	
	free(iter);
	iter = NULL;
	
	return next_node;
}

dll_iterator_t DLLInsertBefore(dll_iterator_t where, void *data)
{
	dll_node_t *new_node = NULL;
	assert(NULL != where);
	assert(NULL != data);
	
	new_node = (dll_node_t *)malloc(sizeof(dll_node_t));
	if(NULL == new_node)
    {
        return ReturnNULLNode(where);
    }
	
	new_node->data = data;
	new_node->next = where;
	
	if(IsHead(where))
	{
		((dll_list_t *)DLLGetData(where->prev))->head = new_node;
		new_node->prev = where->prev;
		where->prev = new_node;
	}
	else
	{
		new_node->prev = where->prev;
		where->prev = new_node;
		new_node->prev->next = new_node;
	}
	
	return new_node;
}

static int IsHead(dll_iterator_t iter)
{
	assert(NULL != iter);
	
	return NULL == DLLNext(DLLPrev(iter));
}

static dll_iterator_t ReturnNULLNode (dll_iterator_t where)
{
    while(NULL != DLLNext(where)) 
    {
        where = DLLNext(where);
    }
    return DLLNext(where);
}

int DLLPushFront(dll_list_t *list, void *data)
{
	if(NULL == DLLNext(DLLInsertBefore(list->head, data)))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}

int DLLPushBack(dll_list_t *list, void *data) 
{
	if(NULL == DLLNext(DLLInsertBefore(list->tail, data)))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}

void *DLLPopFront(dll_list_t *list)
{
	void *data = NULL;
	dll_iterator_t iter_head = NULL;
	assert(NULL != list);
	
	iter_head = DLLBegin(list);
	data = DLLGetData(iter_head);
	DLLRemove(iter_head);
	
	return data;
}

void *DLLPopBack(dll_list_t *list)
{
	void *data = NULL;
	dll_iterator_t iter_last = NULL;
	assert(NULL != list);
	
	iter_last = DLLPrev(DLLEnd(list));
	data = DLLGetData(iter_last);
	DLLRemove(iter_last);
	
	return data;
}

dll_iterator_t DLLFindMatch(is_match_func_t is_match, void *param, 
							const dll_iterator_t from, const dll_iterator_t to)
{
	dll_iterator_t runner = NULL;
	assert(NULL != is_match);
	assert(NULL != from);
	assert(NULL != to);
	
	runner = from;
	while(!DLLIsIterEqual(runner, to)&&
					(!is_match(DLLGetData(runner), param)))
	{
		runner = DLLNext(runner);
	}
	
	return runner;
}

int DLLForEach(action_func_t action_func, void *param, const dll_iterator_t from,
	           const dll_iterator_t to)
{
	int count = 0;
	int num_of_nodes = 0;
	dll_iterator_t runner = NULL;
	
	assert(NULL != action_func);
	assert(NULL != from);
	assert(NULL != to);
	
	runner = (dll_iterator_t)from;
	while(!DLLIsIterEqual(runner, to))
	{
		++num_of_nodes;
		
		if(SUCCESS == action_func(runner->data, param))
		{
			++count;
		}
		
		runner = DLLNext(runner);
	}
	
	return CounterCompare(count, num_of_nodes);
}

int DLLMultiFind(is_match_func_t is_match, void *param,
		         const dll_iterator_t from, const dll_iterator_t to,
		         dll_list_t *result)
{
	int count = 0;
	int num_of_finds = 0;
	dll_iterator_t runner = NULL;
	
	assert(NULL != is_match);
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != result);
	
	runner = (dll_iterator_t)from;
	while(!DLLIsIterEqual(runner, to)&& NULL != DLLNext(runner))
	{
		if(is_match(DLLGetData(runner), param))
		{
			++num_of_finds;
			
			if(SUCCESS == DLLPushBack(result,DLLGetData(runner)))
			{
				++count;
			}
		}
		
		runner = DLLNext(runner);
	}
	
	return CounterCompare(count, num_of_finds);
}

static int CounterCompare(int counter, int compare)
{
	if(counter == compare)
	{
		return SUCCESS;
	}
	
	if(0 == counter)
	{
		return FAILURE;
	}
	
	return counter;
}

dll_iterator_t DLLSplice(dll_iterator_t dest, dll_iterator_t from,
						 dll_iterator_t to)
{
	dll_iterator_t from_prev = NULL;
	dll_iterator_t to_prev = NULL;
	dll_iterator_t dest_prev = NULL;
	
	assert(NULL != dest);
	assert(NULL != from);
	assert(NULL != to);
	
	from_prev = DLLPrev(from);
	to_prev = DLLPrev(to);
	dest_prev = DLLPrev(dest);
	
	if(IsHead(dest)&&IsHead(from))
	{
		((dll_list_t *)DLLGetData(from_prev))->head = to;/* make the node 'to' to be the head of the list*/
		((dll_list_t *)DLLGetData(dest_prev))->head = from;/* linking the head to the 'from' node */
		to->prev = from_prev;/* make the dummy node(from_prev) to be the previous node of 'to' */
		from->prev = dest_prev;/* make the dummy node(dest_prev) to be the previous node of 'from' */
	}	
	else if(IsHead(from))
	{
		((dll_list_t *)DLLGetData(from_prev))->head = to;/* make the node 'to' to be the head of the list*/
		ConnectIters(dest_prev, from);/* connect the from iter to the previous node of dest */
		to->prev = from_prev;/* make the dummy node(from_prev) to be the previous node of 'to' */
	}
	else if(IsHead(dest))
	{
		((dll_list_t *)DLLGetData(dest_prev))->head = from;/* linking the head to the 'from' node */
		from->prev = dest_prev;/* make the dummy node(dest_prev) to be the previous node of 'from' */
		ConnectIters(from_prev, to);/* connect the previous node of iter 'from' to iter 'to' */
	}
	else
	{
		ConnectIters(dest_prev, from);/* connect the from iter to the previous node of dest */
		ConnectIters(from_prev, to);/* connect the previous node of iter 'from' to iter 'to' */
	}
	ConnectIters(to_prev, dest);/* connect the previous node of 'to' to iter dest */
	
	return to_prev;
}

static void ConnectIters(dll_iterator_t iter1, dll_iterator_t iter2)
{
		assert(NULL != iter1);
		assert(NULL != iter2);
		
		iter1->next = iter2;
		iter2->prev = iter1;
}
