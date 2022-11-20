
/*******************************************************************************
*Name : Ran Roni Cohen			 							    	   *
*Reviewar: Ran											   		   *
*Date: 13/03/22																   *
********************************************************************************
                              Singly Linked List
********************************************************************************
Singly Linked List is a data structure that contains a collection of ordered set 
of elements. 

Attributes and policy:
-   Linear data structure
-   Sequential access
-   Holds elements by reference

-------------------------------------------------------------------------------

Operations on DS:
-	Flip the order of the elements in the list
- 	Given a linked list, Check if the linked list has loop or not   
- 	Find first node mutual to both lists.

*******************************************************************************/

#ifndef __SLLExe_H__
#define __SLLExe_H__

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct node node_t;


/*******************************************************************************
Flip
Description: Reverse the slist.
Parameters: 
	- head: Pointer to the head node.
Return value:
	- Return pointer to the head of the reverse slist.
Memory Complexity: O(n)
Time Complexity: O(n)
Notes: 
	  The list must begin and end with a dummy node.
*******************************************************************************/
node_t *Flip(node_t *head);

/*******************************************************************************
HasLoop
Description: Check if the slist has loop or not.
Parameters: 
	- head: Const pointer to the head node.
Return value:
	- In case of success, will return 0.
	- In case of failure, will return 1.
Memory Complexity: O(n)
Time Complexity: O(n)
Notes: 
	  
*******************************************************************************/
int HasLoop(const node_t *head);

/*******************************************************************************
FindIntersection
Description: Check if there is a common iterator in the given lists.
Parameters: 
	- head1: Pointer to the head node of the first slist.
	- head2: Pointer to the head node of the second slist.
Return value:
	- Pointer to the first common element.
Memory Complexity: O(n)
Time Complexity: O(n)
Notes: 
	- In case there is no common element, return NULL.
	  
*******************************************************************************/
node_t *FindIntersection(node_t *head_1, node_t *head_2);
		
#endif /*__SLLExe_H__*/
