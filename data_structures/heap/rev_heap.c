 /*
- Author: Ran Aharon Cohen
- Date:	21.05.22
- Reviewed By: 
- heap.h
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
***************************************************************************/

#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/

#include "d_vector.h"  /* header for dynamic vector funcs */
#include "heap.h" /* header for heap funcs */

#define FREE(ptr) free(ptr);\
                    ptr = NULL;
enum status 
{
	SUCCESS = 0,
	FAILURE
};

typedef enum children 
{
	LEFT = 1,
	RIGHT = 2
}child_side_t;

struct heap
{
	d_vector_t *heap;
	heap_cmp_func_t cmp;
	void *cmp_param;
};

static size_t GetChildIndex(size_t parent_index, child_side_t side);
static void InitHeap(heap_t *heap, heap_cmp_func_t cmp, void *cmp_param);
static size_t GetParentIndex(size_t child_index);
static void Swap(char **ptrX, char **ptrY);
static void HeapifyUp(heap_t *heap);
static void HeapifyDown(heap_t *heap, size_t curr_index, size_t size);
static void *GetMaxChild(void *left_child, void *right_child, heap_t *heap);
void RemoveHelper(heap_t *heap, void *curr_data, size_t curr_index);
void *FindToRemove(heap_t *heap, void *to_remove, is_match_t match_func, 
														void *match_param);
										
static const size_t g_ptr_size = sizeof(size_t); 

heap_t *HeapCreate(heap_cmp_func_t cmp, void *cmp_param)
{
	heap_t *hp = NULL;
	
	assert(NULL != cmp);
	
	hp = (heap_t *)malloc(sizeof(heap_t));
	if(NULL == hp)
	{
		return NULL;
	}
	
	hp->heap = DVectorCreate(g_ptr_size, 20);
	if(NULL == hp->heap)
	{
		FREE(hp);
		return NULL;
	}
	
	InitHeap(hp, cmp, cmp_param);
	
	return hp;
}

static void InitHeap(heap_t *heap, heap_cmp_func_t cmp, void *cmp_param)
{
	heap->cmp = cmp; 
	heap->cmp_param = cmp_param; 
}

void HeapDestroy(heap_t *heap)
{
	assert(NULL != heap);
	
	DVectorDestroy(heap->heap);
	FREE(heap);
}

int HeapPush(heap_t *heap, void *new_data)
{
	int status = SUCCESS;
	
	assert(NULL != heap);
	
	status = DVectorPushBack(heap->heap, &new_data);
	
	if(SUCCESS == status) /* it's only a matter of style, but you can drop the variable and put the PushBack function in the 'if'. */
	{
		HeapifyUp(heap);
	}
	
	return status;
}

static void HeapifyUp(heap_t *heap)
{
	size_t curr_index = 0;
	void **data_parent = NULL; /* if you define them as void ** it will save you the casting in line 115 */
	void **data_child = NULL;
	size_t parent_index = 0;
	int cmp_res = 1;
	
	assert(NULL != heap);
	
	curr_index = HeapSize(heap) - 1;
	
	while(0 < curr_index && 0 < cmp_res)
	{
		parent_index = GetParentIndex(curr_index);
		data_child = DVectorGetElement(heap->heap, curr_index);
		data_parent = DVectorGetElement(heap->heap, parent_index);
		cmp_res = heap->cmp(*data_child,*data_parent,heap->cmp_param); /* too long, split lines (or remove casting) */
				        
		if(0 < cmp_res) /* if you assign data_parent for the first time out of the loop, you can put the cmp function as a condition in the loop and remove this if */
		{
			Swap(*data_child, *data_parent);
		}
		curr_index = parent_index;
	}
}
	
void *HeapPop(heap_t *heap)
{
	size_t size = HeapSize(heap); /* do this after assert NULL != heap */
	void *root = NULL;
	void *last_elem = NULL;
	void *poped_elem = NULL; /* popped :) */
	
	assert(NULL != heap);
	
	root = DVectorGetElement(heap->heap, 0); /* you use 0 in this context in many functions, maybe put it as a MACRO for the root-index? */
	
	last_elem = DVectorGetElement(heap->heap, size - 1);
	poped_elem = *(void **)root; /* here too you can save the casting by defining root as void ** and assigning popped_elem = *root */
	Swap(root, last_elem);
	HeapifyDown(heap, 0, size - 1); /* another MACRO possibility is for the last index in the heap */
	DVectorPopBack(heap->heap);
	
	return poped_elem;
}

static void HeapifyDown(heap_t *heap, size_t curr_index, size_t size) /* I noticed that you always send the same 'size' to this function. so maybe just don't send it and put it as a variable within the function because it's always the same value */
{
	void *data_parent = NULL;
	void *max_child = NULL;
	void *data_right_child = NULL;
	size_t left_child_index = 0;
	size_t right_child_index = 0;
	int cmp_res = 0;
	
	assert(NULL != heap);
	
	left_child_index = GetChildIndex(curr_index, LEFT);
	right_child_index = GetChildIndex(curr_index, RIGHT);
	
	while(left_child_index < size)
	{
		max_child = DVectorGetElement(heap->heap, left_child_index); /* the whole thing between lines 161 and 167 is to get the MaxChild. I think this whold loop will seem much cleaner if all those lines were part of the GetMaxChild function, that simply checks two siblings (if they both exist) and returns the larger one. But it's only a suggestion, if you like it better this way, keep it */
		data_parent = DVectorGetElement(heap->heap, curr_index);
		
		if(right_child_index < size)
		{
			data_right_child = DVectorGetElement(heap->heap, right_child_index);
			max_child = GetMaxChild(max_child, data_right_child, heap);
		}
		
		cmp_res = heap->cmp(*(void **)max_child,*(void **)data_parent,heap->cmp_param); /* again with the void ** and the casting */
		if(0 < cmp_res)
		{
			Swap(data_parent, max_child);   
		}
		
		curr_index = (max_child == data_right_child) ? right_child_index : left_child_index;
		left_child_index = GetChildIndex(curr_index, LEFT);
		right_child_index = GetChildIndex(curr_index, RIGHT);
	}
}

static void *GetMaxChild(void *left, void *right, heap_t *heap)
{
	int cmp_res = 0;
	
	assert(NULL != left);
	assert(NULL != right);
	assert(NULL != heap);
	
	cmp_res = heap->cmp(*(void **)left, *(void **)right, heap->cmp_param);
	
	return (0 < cmp_res ? left : right);
}

void *HeapRemove(heap_t *heap, void *to_remove, is_match_t match_func, void *match_param)
{
	void *curr_elem = NULL;
	
	assert(heap != NULL);
	assert(to_remove != NULL); /* theoretically it can be NULL */
	assert(match_func != NULL);
	
	curr_elem = FindToRemove(heap, to_remove, match_func, match_param);
	
	return curr_elem;
}

void *FindToRemove(heap_t *heap, void *to_remove,
										is_match_t match_func, void *match_param)
{
	size_t curr_index = 0;
	void *curr_data = NULL;
	void *removed_data = NULL;
	
	while(curr_index < HeapSize(heap))
	{
		curr_data = DVectorGetElement(heap->heap, curr_index);
		
		if(match_func(*(void **)curr_data, to_remove, match_param)) /* I know it doesn't matter because the is_match function checks if a == b, but the order should be: to_remove, curr_data, match_param. it may save you some bugs in the future */
		{
			removed_data = *(void **)curr_data;
			RemoveHelper(heap, curr_data, curr_index);	
				
			return removed_data;
		}
		
		++curr_index;
	}
	
	return NULL;
}

void RemoveHelper(heap_t *heap, void *curr_data, size_t curr_index)		
{ /*asserts? */
	Swap(curr_data, DVectorGetElement(heap->heap, HeapSize(heap) - 1));
	HeapifyDown(heap, curr_index, HeapSize(heap) - 1);
	DVectorPopBack(heap->heap);
}

void *HeapPeek(heap_t *heap)
{
	assert(NULL != heap);
	assert(!HeapIsEmpty(heap));
	
	return *(void **)DVectorGetElement(heap->heap, 0);
}

int HeapReplace(heap_t *heap, void *new_data); /* remove */
/* O(lon n)*/

size_t HeapSize(const heap_t *heap)
{
	assert(NULL != heap);
	
	return DVectorSize(heap->heap);
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(NULL != heap);
	
	return !HeapSize(heap); /* or just check if the DVector is empty */
}

static size_t GetParentIndex(size_t child_index)
{
    assert(0 != child_index);
    
    return ((child_index - 1) / 2);
}

static size_t GetChildIndex(size_t parent_index, child_side_t side)
{
    return ((2 * parent_index) + side);
}

static void Swap(char **ptrX, char **ptrY)
{
	void *temp = NULL;

    assert(NULL != ptrX);
    assert(NULL != ptrY);

    temp = *ptrX;
    *ptrX = *ptrY;
    *ptrY = temp;
}

void PrintHeap(heap_t *heap)
{
	size_t multi = 2;
	size_t go_down = 2;
	size_t i = 0;
	
	printf("\n");
	for(i = 0; i < HeapSize(heap); ++i)
	{
		
		if(0 == i)
		{
			printf("%d\n", *(int *)*(void **)DVectorGetElement(heap->heap, i));
		}
		else if(i == go_down)
		{
			printf("%d \n", *(int *)*(void **)DVectorGetElement(heap->heap, i));
			multi = multi * 2;
			go_down = multi + 2;
		}
		else
		{
			printf("%d ", *(int *)*(void **)DVectorGetElement(heap->heap, i));
		}
	}
	printf("\n");
}

