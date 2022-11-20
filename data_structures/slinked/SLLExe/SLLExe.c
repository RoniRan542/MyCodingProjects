#include <stddef.h>
#include <assert.h>
#include <stdlib.h>

#include "SLLExe.h"

struct node
{
    void *data;
    struct node *next;
};


size_t Count(node_t *head);

node_t *Flip(node_t *head)
{
	node_t *next_node = NULL;
	node_t *pre_node = NULL;
	node_t *curr_node = head;
	assert(NULL != head);
	
	while(NULL != curr_node->next)
	{
		next_node = curr_node->next;
		curr_node->next = pre_node;
		pre_node = curr_node;
		curr_node = next_node;
	}
	head->next = curr_node;
	
	return pre_node;
}

int HasLoop(const node_t *head)
{
	node_t *step_p;
	node_t *double_step_p;
	assert(NULL != head);
	
	step_p = (node_t *)head;
	double_step_p = (node_t *)head;
	
	while(step_p && double_step_p && double_step_p->next)
	{
		step_p = step_p->next;
		double_step_p = (double_step_p->next)->next;
		if(step_p == double_step_p)
		{
			return 1;
		}
	}
	
	return 0;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t count = 0;
	size_t count1 = 0;
	size_t count2 = 0;

	assert(NULL != head_1);
	assert(NULL != head_2);
	count1 = Count(head_1);
	count2 = Count(head_2);
	
	
	if(count1>count2)
	{
		count = count1 - count2;
		while(count--)
		{
			head_1 = head_1->next;
		}
	}
	else
	{
		count = count2 - count1;
		while(count--)
		{
			head_2 = head_2->next;
		}
	}
	
	while(head_1->next && head_2->next)
	{
		if(head_1 == head_2)
		{
			return head_1;
		}
		
		head_1 = head_1->next;
		head_2 = head_2->next;
	}
	
	return (void *)0; /* NULL */
}

size_t Count(node_t *head)
{
	size_t counter = 0;
	assert(NULL != head);
	
	while(NULL != head->next)
	{
		++counter;
		head = head->next;
	}
		
	return counter;
}
