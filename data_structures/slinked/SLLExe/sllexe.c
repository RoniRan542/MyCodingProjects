#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/
#include "sllexe.h"

static size_t CountNodes(const node_t *head);

enum status
{
	SUCCESS = 0,
	FAILURE
};

struct node
{
    void *data;
    struct node *next;
};

node_t *Flip(node_t *head)
{
	node_t *previous = NULL;
	node_t *current = head;
	node_t *next = NULL;
	
	while (NULL != current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	head = previous;
	
	return head;
}


int HasLoop(const node_t *head)
{
	node_t *pointerbyone = (void *)head;
	node_t *pointerbytwo = (void *)head;
	
	while (NULL !=  pointerbyone && NULL !=  pointerbytwo)
	{
		pointerbyone = pointerbyone->next;
		pointerbytwo = pointerbytwo->next->next;
		
		if (pointerbyone == pointerbytwo)
		{
			return SUCCESS;
		}
	}
	return FAILURE;	
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t diff = 0;
	
	assert(NULL != head_1);
	assert(NULL != head_2);
	
	diff = (CountNodes(head_1) - CountNodes(head_2));
	
	if (diff)
	{
		while (0 != diff)
		{
			head_1 = head_1->next;
			--diff;
		}
	}
	else
	{
		while (0 != diff)
		{
			head_2 = head_2->next;
			++diff;
		}
	}
	
	while (NULL != head_1)
	{
		if (head_1 == head_2)
		{
			return head_1;
		}
		head_1 = head_1->next;
		head_2 = head_2->next;
	}
	
	return NULL;
}


static size_t CountNodes(const node_t *head)
{
	size_t count = 0;
	node_t *runner = (void *)head;
	
	while (NULL != runner)
	{
		++count;
		runner = runner->next;
	}
	
	return count;
}
