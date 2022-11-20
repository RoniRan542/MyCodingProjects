#include <stdlib.h>/*malloc, free*/
#include <assert.h>/*assert*/
#include <limits.h>/*CHAR_BIT*/

#include "avl.h"
#define FREE(var) free(var);\
                    var = NULL;
#define GETHEIGHT(children) ( children ? (children->height) : (0) )
#define MAX(x, y) ( (x) > (y) ? (x) : (y) )

typedef struct avl_node node_t;

enum Status
{
	SUCCESS = 0,
	FAILURE = 1
};

enum children
{
	LEFT = 0,
	RIGHT = 1,
	NUM_OF_CHILDREN = 2
};

struct avl_node
{
	node_t *children[NUM_OF_CHILDREN];
	void *data;
	size_t height;
};
	
struct avl
{
	node_t *root;
	avl_cmp_func_t cmp; 
	void *param;
};



typedef int(*ordered_func_t)(node_t *root, avl_action_func_t act_func, void *param);

static size_t UpdateNodeHeightByChilds(node_t *node);
static int PreOrder(node_t *root, avl_action_func_t act_func, void *param);
static int InOrder(node_t *root, avl_action_func_t act_func, void *param);
static int PostOrder(node_t *root, avl_action_func_t act_func, void *param);
static void RecDestroy(node_t *node);
static node_t *RecRemove(avl_t *avl, node_t *node, const void *to_remove);
static node_t *RemoveAndFix(avl_t *avl, node_t *node);
static void InitNode(node_t *node,void *data,size_t height);
static node_t *InsertRecursive(avl_t *avl, node_t *root, node_t *new_node);
static int GetChildSide(int avl_result);
static node_t *RecFind(node_t *curr, const void *key, avl_cmp_func_t cmp, void *param);
static int Count(void *data, void *param);
static node_t *DoRotationIfNeeded(node_t *parent);
static size_t GetNodeHeight(node_t *node);
static node_t *HandleHeavySide(node_t *parent, int side);
static node_t *HandleMixedSides(node_t *parent, node_t *child, int side);
static node_t *HandleSameSides(node_t *parent, node_t *child, int side);

/* Traversal LUT */
static const ordered_func_t g_for_each_lut[NUM_OF_TYPES] = {&PreOrder, &InOrder, &PostOrder};

avl_t *AVLCreate(avl_cmp_func_t cmp, void *param)
{
	avl_t *avl_tree = NULL; 
	assert(NULL != cmp);
	
	avl_tree = (avl_t *)malloc(sizeof(avl_t)); 
	if(NULL == avl_tree)
	{
		return NULL;
	}
	
	avl_tree->cmp = cmp;
	avl_tree->param = param;
	avl_tree->root = NULL;
	
	return avl_tree;
}

void AVLDestroy(avl_t *avl)
{
    assert(NULL!= avl);
    
    RecDestroy(avl->root);
    FREE(avl);
}

static void RecDestroy(node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	RecDestroy(node->children[LEFT]);
	RecDestroy(node->children[RIGHT]);
		
	FREE(node);
}

static void InitNode(node_t *node,void *data,size_t height)
{
	assert(NULL != node);
	
	node->data = data;
	node->height = height;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
}

void AVLRemove(avl_t *avl, const void *to_remove)
{	
	assert(NULL != avl);
	
	avl->root = RecRemove(avl, avl->root, to_remove);
}

static node_t *RecRemove(avl_t *avl, node_t *node, const void *to_remove)
{
	int cmp_res = 0;
	node_t *child_node = NULL;
	
	assert(NULL != avl->cmp);
	
	cmp_res = avl->cmp(to_remove, node->data, avl->param);
	if (cmp_res == 0)
	{
		return RemoveAndFix(avl, node);
	}
	
	child_node = RecRemove(avl, node->children[GetChildSide(cmp_res)], to_remove);
	node->children[GetChildSide(cmp_res)] = child_node;
	node->height = UpdateNodeHeightByChilds(node);
	node = DoRotationIfNeeded(node);
	
	return node;
}

static node_t *RemoveAndFix(avl_t *avl, node_t *node)
{
	node_t *right_child = NULL;
	node_t *left_child = NULL;
	
	assert(NULL != node);
	assert(NULL != avl->cmp);
	
	right_child = node->children[RIGHT];
	left_child = node->children[LEFT];
	
	free(node);
	node = NULL;
	
	return (left_child != NULL) ? InsertRecursive(avl, right_child, left_child) : right_child;
}


int AVLInsert(avl_t *avl, void *new_data)
{
	node_t *new_node = NULL;
	node_t *root = avl->root;
	
	assert(NULL != avl);
	
	new_node = (node_t *)malloc(sizeof(node_t)); 
	if(NULL == new_node)
	{
		return 1;
	}
	
	InitNode(new_node, new_data, 1);
	avl->root = InsertRecursive(avl, root, new_node);
	
	return 0;
}

static node_t *InsertRecursive(avl_t *avl, node_t *root, node_t *new_node)
{
	int child_side = LEFT;
	node_t *child = NULL;
	
	assert(NULL != avl);
	assert(NULL != new_node);
	
	if(NULL == root)
	{
		return new_node;
	}
	
	child_side = GetChildSide(avl->cmp(new_node->data, root->data, NULL));
	child = root->children[child_side];
	root->children[child_side] = InsertRecursive(avl, child, new_node);
	UpdateNodeHeightByChilds(root);
	
	return DoRotationIfNeeded(root);;
}

static int GetChildSide(int avl_result)
{    
    return !(((unsigned int)(avl_result)) >> ((sizeof(int) * CHAR_BIT) - 1));
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);
	
	return (0 == GETHEIGHT(avl->root));
}

size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);
	
	return GETHEIGHT(avl->root);
}

int AVLForEach(avl_t *avl, avl_action_func_t act_func, void *param, 
				int order_type)
{
	node_t *root = NULL;
	
	assert(NULL != act_func);
	assert(NULL != avl);
	assert(PRE <= order_type && POST >= order_type);
	
	root = avl->root;
	
	return g_for_each_lut[order_type](root, act_func, param);	
}

static int PreOrder(node_t *root, avl_action_func_t act_func, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != act_func);
	
	if(NULL != root)
	{
		
		status = act_func(root->data, param);
		
		
		if(SUCCESS != status)
		{
			return FAILURE;
		}
		
		status = PreOrder(root->children[LEFT], act_func, param);
		
		if(SUCCESS != status)
		{
			return FAILURE;
		}
		
		status = PreOrder(root->children[RIGHT], act_func, param);	
		
		
	}
	
	return status;
}

static int InOrder(node_t *root, avl_action_func_t act_func, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != act_func);
	
	if(NULL != root)
	{
		status = InOrder(root->children[LEFT], act_func, param);
		if(SUCCESS != status)
		{
			return FAILURE;
		}
		
		status = act_func(root->data, param);
		if(SUCCESS != status)
		{
			return FAILURE;
		}
		
		status = InOrder(root->children[RIGHT], act_func, param);	
	}
	
	return status;
}

static int PostOrder(node_t *root, avl_action_func_t act_func, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != act_func);
	
	if(NULL != root)
	{
		status = InOrder(root->children[LEFT], act_func, param);
		if(SUCCESS != status)
		{
			return FAILURE;
		}
		
		status = InOrder(root->children[RIGHT], act_func, param);
		if(SUCCESS != status)
		{
			return FAILURE;
		}
		
		status = act_func(root->data, param);	
	}
	
	return status;
}


void *AVLFind(const avl_t *avl, const void *key)
{
	node_t *found = NULL;
	
	assert(NULL != avl);
	
	found = RecFind(avl->root, key, avl->cmp, avl->param);
	
	return (found == NULL) ? NULL : found->data;
}

static node_t *RecFind(node_t *curr, const void *key, avl_cmp_func_t cmp, void *param)
{
	int cmp_result = 0;
	int norm_side = LEFT;
	
	assert(NULL != cmp);
	
	if(NULL == curr)
	{
		return NULL;
	}
	
	cmp_result = cmp(key, curr->data, param);
	if(0 == cmp_result)
	{
		return curr;
	}
	
	norm_side = GetChildSide(cmp_result);

	return RecFind(curr->children[norm_side], key, cmp, param);
}

size_t AVLCount(const avl_t *avl)
{
	size_t param = 0;
	
	assert(NULL != avl);
	
	if(1 != AVLIsEmpty(avl))
	{
		AVLForEach((avl_t *)avl, &Count, &param, PRE);
	}
	
	return param;
}

static int Count(void *data, void *param)
{
	(void)data;
	*(size_t *)param += 1LU;
	
	return SUCCESS;
}

static node_t *DoRotationIfNeeded(node_t *parent)
{
    size_t height_left_child = 0;
    size_t height_right_child = 0;
    
    assert(NULL != parent);
    
    height_left_child = GetNodeHeight(parent->children[LEFT]);
    height_right_child = GetNodeHeight(parent->children[RIGHT]);
    
    if(height_left_child + 1 < height_right_child)
    {
        parent = HandleHeavySide(parent, RIGHT);        
    }
    else if(height_right_child + 1 < height_left_child)
    {
        parent = HandleHeavySide(parent, LEFT);
    }
    
    return parent;
}

static size_t GetNodeHeight(node_t *node)
{
    return (NULL == node ? 0 : node->height);
}

static node_t *HandleHeavySide(node_t *parent, int side)
{
    size_t left_grandchild_height = 0;
    size_t right_grandchild_height = 0;
	node_t *child = NULL;
	
    assert(NULL != parent);
    
	child = parent->children[side];
    left_grandchild_height = GetNodeHeight(child->children[side]);
    right_grandchild_height = GetNodeHeight(child->children[!side]);
    if(right_grandchild_height <= left_grandchild_height)
    {
        return HandleSameSides(parent, child, side);        
    }
    else
    {
        return HandleMixedSides(parent, child, side);
    }
}

static node_t *HandleSameSides(node_t *parent, node_t *child, int side)
{
    assert(NULL != parent);
    assert(NULL != child);
    
	UpdateNodeHeightByChilds(parent);
    parent->children[side] = child->children[!side];
    child->children[!side] = parent;
    UpdateNodeHeightByChilds(parent);
    UpdateNodeHeightByChilds(child);
    
    return child;    
}

static node_t *HandleMixedSides(node_t *parent, node_t *child, int side)
{
    assert(NULL != parent);
    assert(NULL != child);
    child = HandleSameSides(child,child->children[!side],!side);
    return HandleSameSides(parent, child, side);    
}

static size_t UpdateNodeHeightByChilds(node_t *node)
{
	node->height = MAX(GETHEIGHT(node->children[LEFT]),
										GETHEIGHT(node->children[RIGHT])) + 1;
	return node->height;
}
