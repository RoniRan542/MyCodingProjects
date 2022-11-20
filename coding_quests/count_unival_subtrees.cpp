/********************************************************
*Name : Ran Aharon Cohen	 	    			        *
*Date: 	19.07.22		            		            *
*Description : count unival sub trees.                  *
*A unival tree (which stands for "universal value")     *
*is a tree where all nodes under it have the same value.*
*Example:                                               *
  0                                                     *
  / \                                                   *
 1   0                                                  *
    / \         Output: 5                               *
   1   0                                                *
  / \                                                   *
 1   1                                                  *
*********************************************************/
#include <iostream>

typedef struct node node_t;

struct node
{
    node_t *Left;
    node_t *Right;
};

bool CountUnivalSubtrees(node_t *root, size_t *unival_sum)
{
    bool left = true;
    bool right = true;

    if (root->Left == NULL && root->Right == NULL)
    {
        *unival_sum += 1;
        return true;
    }

    if (CountUnivalSubtrees(root->Left, unival_sum) &&
        CountUnivalSubtrees(root->Right, unival_sum) &&
        root->Left == root->Right)
    {
        *unival_sum += 1;
        return true;
    }

    return false;
}