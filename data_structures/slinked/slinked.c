#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../include/slinked.h"

enum status
{
	SUCCESS = 0,
	FAILURE
};

struct s_list_node
{
    void *data;
    s_list_node_t *next;
};

struct s_linked_list 
{
    s_list_node_t *head;
    s_list_node_t *tail;
};

s_linked_list_t *SLinkedListCreate(void)
{
	s_linked_list_t *slinked;
	s_list_node_t *dummy_node;
	slinked = (s_linked_list_t *)malloc(sizeof(s_linked_list_t));
	if(NULL == slinked)
	{
		return NULL;
	}
	
	dummy_node = (s_list_node_t *)malloc(sizeof(s_list_node_t));
	if(NULL == dummy_node)
	{
		return NULL;
	}
	dummy_node->data = slinked;
	dummy_node->next = NULL;
	
	slinked->head = dummy_node;
	slinked->tail = dummy_node;
	
	return slinked;
}

void SLinkedListDestroy(s_linked_list_t *list)
{
	s_list_iter_t iter;
	assert(NULL != list);
	
	iter = list->head;
	while(NULL != iter->next)
	{
		iter = SLinkedListRemove(iter);
	}
	free(list->head);
	free(list);
	list = NULL;
}

s_list_iter_t SLinkedListBegin(const s_linked_list_t *list)
{
	s_list_iter_t iter;
	assert(NULL != list);
	iter = list->head;
	return iter;
}

s_list_iter_t SLinkedListEnd(const s_linked_list_t *list)
{
	
	assert(NULL != list);
	
	return list->tail;
}

s_list_iter_t SLinkedListNext(const s_list_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->next;
}

void *SLinkedListGetData(const s_list_iter_t iter)
{
	assert(NULL != iter);
	return iter->data;
}

void SLinkedListSetData(s_list_iter_t iter, const void *new_data)
{
	assert(NULL != iter);
	assert(NULL != new_data);
	iter->data = (void *)new_data;
}

int SLinkedListIsIterEqual(const s_list_iter_t iter1, const s_list_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	return iter1 == iter2;
}

s_list_iter_t SLinkedListInsertBefore(s_list_iter_t where, const void *data)
{
	s_list_node_t *ptr_node;
	assert(NULL != where);
	assert(NULL != data);
	ptr_node = (s_list_node_t *)malloc(sizeof(s_list_node_t));
	if(NULL == ptr_node)
	{
		while(NULL != where->next)
		{
			where = where->next;
		}
		return where;
	}
	ptr_node->data = where->data;
	ptr_node->next = where->next;
	where->data = (void *)data;
	where->next = ptr_node;
	
	if(NULL == ptr_node->next)
	{
		((s_linked_list_t *)(ptr_node->data))->tail = ptr_node;/* dummy node*/
	}
	
	return where;
}

int SLinkedListIsEmpty(const s_linked_list_t *list)
{
	assert(NULL != list);
	return NULL == SLinkedListBegin(list)->next;
}

s_list_iter_t SLinkedListRemove(s_list_iter_t iter)
{
	s_list_iter_t new_iter = NULL; 
	assert(NULL != iter);
	new_iter = SLinkedListNext(iter);
	iter->data = new_iter->data;
	iter->next = new_iter->next;
	
	if(NULL == iter->next)
	{
		((s_linked_list_t *)(iter->data))->tail = iter;/* dummy node*/
	}
	
	free(new_iter);
	
	return iter;
}

size_t SLinkedListCount(const s_linked_list_t *list)
{
	size_t count = 0;
	s_list_iter_t iter;
	assert(NULL != list);
	iter = list->head;
	
	while(NULL != iter->next)
	{
		++count;
		iter = SLinkedListNext(iter);
	}
	
	return count;
}

s_list_iter_t SLinkedListFind(match_func_t is_match, void *param, 
s_list_iter_t from, s_list_iter_t to)
{	
	assert(NULL != is_match);
	assert(NULL != from);
	assert(NULL != to);

	while(!SLinkedListIsIterEqual(from, to)&& NULL != from->next)
	{
		if(is_match(from->data, param))
		{
			return from;
		}
		
		from = SLinkedListNext(from);
	}
	
	return from;
}

int SLinkedListForEach(action_func_t action_func, void *param,
 s_list_iter_t from, s_list_iter_t to)
{
	assert(NULL != action_func);
	assert(NULL != from);
	assert(NULL != to);

	while(!SLinkedListIsIterEqual(from, to))
	{
		if(SUCCESS != action_func((void *)&from->data, param))
		{
			return FAILURE;
		}
		
		from = SLinkedListNext(from);
	}

	return SUCCESS;
}

s_linked_list_t *SLinkedListAppend(s_linked_list_t *dest, s_linked_list_t *src)
{
	s_list_iter_t dest_tail = NULL;
    s_list_iter_t src_head = NULL;
    s_list_iter_t src_tail = NULL;

    assert(NULL != dest);
    assert(NULL != src);

    dest_tail = SLinkedListEnd(dest);
    src_head = SLinkedListBegin(src);
    src_tail = SLinkedListEnd(src);

    dest_tail->next = src_head;
    SLinkedListRemove(dest_tail);
    src_tail->data = dest;
    dest->tail = src_tail; 
	
	(src->head)->data = src;
    src->tail = src->head;
    (src->head)->next = NULL;
	
	return dest;
}

void SLinkedListPrintList(s_linked_list_t *list)
{
	s_list_node_t *node = list->head;
	while(NULL != (node->next)->next)
	{
		printf("(%d)->",*(int *)node->data);
		node = node->next;
	}
	
	printf("(%d)\n\n",*(int *)node->data);
}
