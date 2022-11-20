#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "SLLExe.h"

struct node
{
    void *data;
    struct node *next;
};

void PrintList(node_t *head);

int main()
{
	node_t *list1_node5 = malloc(sizeof(node_t *));  /*dummy*/
	node_t *list1_node4 = malloc(sizeof(node_t *));  
	node_t *list1_node3 = malloc(sizeof(node_t *));  
	node_t *list1_node2 = malloc(sizeof(node_t *));  
	node_t *list1_node1 = malloc(sizeof(node_t *));  
	
	node_t *list2_node5 = malloc(sizeof(node_t *));  /*dummy*/
	node_t *list2_node4 = malloc(sizeof(node_t *));  
	node_t *list2_node3 = malloc(sizeof(node_t *));  
	node_t *list2_node2 = malloc(sizeof(node_t *));  
	node_t *list2_node1 = malloc(sizeof(node_t *));  
	int v1,v2,v3,v4;
	v1 = 1;
	v2 = 2;
	v3 = 3;
	v4 = 4;
	
	
	
	/* list 1*/
	list1_node1->data = &v1; 
	list1_node1->next = list1_node2;
	
	list1_node2->data = &v2; 
	list1_node2->next = list1_node3;
	
	list1_node3->data = &v3; 
	list1_node3->next = list1_node4;
	
	list1_node4->data = &v4; 
	list1_node4->next = list1_node5;

	list1_node5->data = NULL; /*dummy*/
	list1_node5->next = NULL;
	
	/* list 2*/
	list2_node1->data = &v4; 
	list2_node1->next = list2_node2;
	
	list2_node2->data = &v3; 
	list2_node2->next = list2_node3;
	
	list2_node3->data = &v2; 
	list2_node3->next = list2_node4;
	
	list2_node4->data = &v1; 
	list2_node4->next = list1_node3;

	list2_node5->data = NULL; /*dummy*/
	list2_node5->next = NULL;
	/*PrintList(node1);
	PrintList(Flip( node1));
	
	node4->next = node3;
	
	printf("1 == %d\n",HasLoop(node1));
	
	node4->next = node5;
	
	printf("0 == %d\n",HasLoop(node1));*/
	
	printf("%d\n",*(int *)FindIntersection(list1_node1, list2_node1)->data);
	return 0;
}

void PrintList(node_t *head)
{

	while(NULL != (head->next)->next)
	{
		printf("(%d)->",*(int *)head->data);
		head = head->next;
	}
	printf("(%d)\n\n",*(int *)head->data);
}
