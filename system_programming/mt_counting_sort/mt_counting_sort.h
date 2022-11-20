/************************************************
*Name: Ran Aharon Cohen                              *
*Reviewer:                                      *
*Date: 04.07.22                                 *
*File: mt_counting_sort.h                                   *
************************************************/

#ifndef __MT_COUNT_SORT_H__
#define __MT_COUNT_SORT_H__

/******************************************************************************
MtCountingSort
Description: counting sort is a sorting algorithm that sorts the elements of an 
array by counting the number of occurrences of each unique element in the array
Parameters: 
	- arr - the array to sort
	- length - the lenght of the giben array
	- threads_amount - amount of processing threads
Return value:
	- zero on success, non-zero value on fail
Time Complexity: O(n)
Notes: - if given a NULL pointer, behavior is undefined
	   - length must be bigger than zero
*****************************************************************************/

int MtCountingSort(unsigned char *arr, size_t len, size_t threads_amount); 

#endif /* __MT_COUNT_SORT_GUARD__ */


