/*Author: Ran Aharon Cohen
 Date: 28.04.22
 Reviewed By: Hamotal
 */
 
#include <assert.h>/*for assert*/
#include <stdlib.h>/*for malloc, free*/
#include <limits.h>/*for char_bit*/

#include "bst.h"
#define ROOT (bst->dummy_root.children[LEFT])
#define NORMALIZE(num) !((unsigned)num >> (BYTE - 1 + BYTE * (int_size_g - 1)))
#define FREE(var) free(var);\
                    var = NULL;
enum status
{
	SUCCESS = 0,
	FAILURE
};

enum children
{
	LEFT = 0,
	RIGHT,
	NUM_OF_CHILDREN
};

typedef struct bst_node bst_node_t;
struct bst_node
{
	void *data;
	bst_node_t *parent;
	bst_node_t *children[NUM_OF_CHILDREN];
};

struct bst
{
	bst_node_t dummy_root; /*(dummy will hold the biggest num possible)*/
	bst_cmp_func_t cmp; 
	void *param;
};

static short GetNumOfChildren(bst_iter_t iter);
static bst_iter_t GetIterParent(bst_iter_t iter);
static bst_iter_t GetIterRightChild(bst_iter_t iter);
static bst_iter_t GetIterLeftChild(bst_iter_t iter);
static int GetChildSide(int cmp_result);
static void RemoveChildlessNode(bst_iter_t iter);
static void RemoveSingleChildNode(bst_iter_t iter);
static int AmIRightOrLeft(bst_iter_t child);
static void SetNewNode(bst_node_t *new_node, bst_iter_t iter_parent, 
								void *data, int child_side);
static bst_iter_t GoRightThenLeftDepth(bst_iter_t iter);
static bst_iter_t FindRightParent(bst_iter_t iter);
static bst_iter_t GoLeftThenRightDepth(bst_iter_t iter);
static bst_iter_t FindLeftParent(bst_iter_t iter);

bst_t *BSTCreate(bst_cmp_func_t cmp, void *param)
{
	bst_t *tree = NULL;
	bst_node_t dummy = {NULL, NULL,{NULL, NULL}};
	
	assert(NULL!= cmp);
	
	tree = (bst_t *)malloc(sizeof(bst_t));
	if(NULL == tree)
	{
		return NULL;
	}
	
	tree->dummy_root = dummy;
	tree->cmp = cmp;
	tree->param = param;
	
	return tree;
}

void BSTDestroy(bst_t *bst)
{
    assert(NULL!= bst);
    
    while(!BSTIsEmpty(bst))
    {
        BSTRemove(BSTBegin(bst));
    }
    
    FREE(bst);
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);
	
	return NULL == ROOT;
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t iter = NULL;
	bst_iter_t iter_parent = NULL;
	int child_side = LEFT;
	bst_node_t *new_node = NULL;
	
	assert(NULL != bst);
	assert(BSTEnd(bst) == BSTFind(bst,BSTBegin(bst),BSTEnd(bst),data));
	
	iter_parent = &bst->dummy_root;
	iter = iter_parent->children[LEFT];
	
	while(NULL != iter)
	{
		child_side = GetChildSide(bst->cmp(data, iter->data, NULL));
		iter_parent = iter;
		iter = iter->children[child_side];
	}

	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
    {
        return BSTEnd(bst);
    }

	SetNewNode(new_node, iter_parent, data, child_side);
	
	return new_node;
}

static void SetNewNode(bst_node_t *new_node, bst_iter_t iter_parent, 
							void *data, int child_side)
{
	new_node->data = data;
	new_node->parent  = iter_parent;
	new_node->children[RIGHT] = NULL;
	new_node->children[LEFT] = NULL;
	iter_parent->children[child_side] = new_node;
}

static int GetChildSide(int cmp_result)
{    
    return !(((unsigned int)(cmp_result)) >> ((sizeof(int) * CHAR_BIT) - 1));
}

void BSTRemove(bst_iter_t where)
{
	bst_iter_t prev = NULL;
	
	assert(GetIterParent(where));
	
	switch(GetNumOfChildren(where))
	{
		case 0:
				RemoveChildlessNode(where);
				break;
			
		case 1:
				RemoveSingleChildNode(where);
				break;
			
		case 2:
				prev = BSTPrev(where);
				where->data = prev->data;
				
				if(GetNumOfChildren(prev))
				{
					RemoveSingleChildNode(prev);
				}
				else
				{
					RemoveChildlessNode(prev);
				}
				break;
	}
}

static void RemoveChildlessNode(bst_iter_t iter)
{	
	bst_iter_t parent = NULL;
	
	parent = GetIterParent(iter);
	parent->children[AmIRightOrLeft(iter)] = NULL;
	
	FREE(iter);
}

static void RemoveSingleChildNode(bst_iter_t iter)
{	
	bst_iter_t parent = NULL;																
	bst_iter_t child = NULL;		
															
	parent = GetIterParent(iter);
	child = (NULL != GetIterRightChild(iter)) ?
					 GetIterRightChild(iter) : GetIterLeftChild(iter);
	parent->children[AmIRightOrLeft(iter)] = child;
	child->parent = parent;
	
	FREE(iter);
}

static int AmIRightOrLeft(bst_iter_t child)
{
	bst_iter_t parent = NULL;
	parent = GetIterParent(child);

	return BSTIterIsEqual(GetIterRightChild(parent), child);
}

static bst_iter_t GetIterParent(bst_iter_t iter)
{
	return iter->parent;
}

static bst_iter_t GetIterRightChild(bst_iter_t iter)
{
	return iter->children[RIGHT];
}

static bst_iter_t GetIterLeftChild(bst_iter_t iter)
{	
	return iter->children[LEFT];
}

static short GetNumOfChildren(bst_iter_t iter)
{
	short num_of_ch = 0;
	assert(NULL != iter);
	
	num_of_ch += (NULL != iter->children[RIGHT]); 
	num_of_ch += (NULL != iter->children[LEFT]);
	 
	return num_of_ch;
}


bst_iter_t BSTBegin(bst_t *bst)
{
	bst_iter_t iter = NULL;
	
	assert(NULL != bst);
	
	iter = &bst->dummy_root;
	
	while(NULL != iter->children[LEFT])
	{
		iter = iter->children[LEFT];
	}
	
	return iter;
}

bst_iter_t BSTEnd(bst_t *bst)
{
	assert(NULL != bst);
	
	return &bst->dummy_root;
}

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return iter1 == iter2;
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	assert(NULL != iter);
	assert(NULL != iter->parent);
	
	if(NULL != GetIterRightChild(iter))
	{
		return GoRightThenLeftDepth(iter);
	}
	
	return FindRightParent(iter);
}

static bst_iter_t GoRightThenLeftDepth(bst_iter_t iter)
{
	iter = GetIterRightChild(iter);
	
	while(NULL != GetIterLeftChild(iter))
	{
		iter = GetIterLeftChild(iter);
	}
	
	return iter;
} 

static bst_iter_t FindRightParent(bst_iter_t iter)
{
	while(LEFT != AmIRightOrLeft(iter))
	{
		iter = GetIterParent(iter);
	}
	
	return GetIterParent(iter);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	assert(NULL != iter);
	
	if(NULL != GetIterLeftChild(iter))
	{
		return GoLeftThenRightDepth(iter);
	}
	
	return FindLeftParent(iter);
}

static bst_iter_t GoLeftThenRightDepth(bst_iter_t iter)
{
	iter = GetIterLeftChild(iter);
	while(NULL != GetIterRightChild(iter))
	{
		iter = GetIterRightChild(iter);
	}
	
	return iter;
}

static bst_iter_t FindLeftParent(bst_iter_t iter)
{
	while(RIGHT != AmIRightOrLeft(iter))
	{
		iter = GetIterParent(iter);
	}
	
	return GetIterParent(iter);
}

void *BSTGetData(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->data;
}

size_t BSTCount(const bst_t *bst)
{
	 bst_iter_t iter = NULL;
	 bst_iter_t dummy  = BSTEnd((bst_t *)bst);
	 size_t count = 0;
	 
	 assert(NULL != bst);
	 
	 iter = BSTBegin((bst_t *)bst);
	 while(!BSTIterIsEqual(iter, dummy))
	 {
	 	iter = BSTNext(iter);
	 	++count;
	 }
	 
	 return count;
}

bst_iter_t BSTFind(bst_t *bst, bst_iter_t from, bst_iter_t to, void *data)
{
	assert(NULL != bst);
	assert(NULL != to);
	assert(NULL != from);
	
	while(!BSTIterIsEqual(from, to) && (0 != bst->cmp(data, BSTGetData(from), NULL)))
	{
		from = BSTNext(from);
	}
	
	return from;
}

int BSTForeach(bst_iter_t from, bst_iter_t to, 
					bst_action_func_t act_func, void *param)
{
	assert(NULL != act_func);
	assert(NULL != to);
	assert(NULL != from);
	
	while(!BSTIterIsEqual(from, to))
	{
		if(SUCCESS != act_func(from->data, param))
		{
			return FAILURE;
		}
		
		from = BSTNext(from);
	}
	
	return SUCCESS;
}
