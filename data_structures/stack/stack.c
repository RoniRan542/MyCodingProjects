/*****************************************************************
*Name : Ran Aharon Cohen	 								 *
*Reviewar: Tom 													 *
*Date: 7.3.22													 *
*Pass Valgrind: YES												 *
*aprovved : 												 *
*Description : Stack										 *
******************************************************************/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/

#include "stack.h" /*typedef stack_t*/

struct Stack 
{
    void *data;
    size_t size;
    size_t element_size;
    size_t capacity;
};

stack_t *StackCreate(size_t capacity,size_t element_size)
{
	stack_t *stack = malloc(sizeof(stack_t));
	if (NULL == stack)
	{
		return NULL;
	}
	stack->data = malloc(capacity * element_size);
	if (NULL == stack->data)
	{
		StackDestroy(stack);
		return NULL;
	}
	
	stack->size = 0;
	stack->element_size = element_size;
	stack->capacity = capacity;

	return stack;
}

void StackPop(stack_t *stack)
{
	--stack->size;
}

void StackPush(stack_t *stack, void *data)
{
	size_t offset = stack->size * stack->element_size;
	memcpy((char *)stack->data + offset , data , stack->element_size);
	++stack->size;
}

void *StackPeek(const stack_t *stack)
{
	char *runner = stack->data;
	runner += (((stack->size) - 1) * (stack->element_size));
	
	return runner;
}

int StackIsEmpty(const stack_t *stack)
{
	return (0 == StackSize(stack));
}

size_t StackSize(const stack_t *stack)
{
	return stack->size;
}

size_t StackCapacity(const stack_t *stack)
{
	return stack->capacity;
}

void StackDestroy(stack_t *stack)
{
	free (stack->data);
	stack->data = NULL;
	free (stack);
	stack = NULL;
}

