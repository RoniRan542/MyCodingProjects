/*******************************************************************************


				 █████   █████  █████████    █████████
				░░███   ░░███  ███░░░░░███  ███░░░░░███
				 ░███    ░███ ░███    ░░░  ░███    ░███
				 ░███    ░███ ░░█████████  ░███████████
				 ░░███   ███   ░░░░░░░░███ ░███░░░░░███
				  ░░░█████░    ███    ░███ ░███    ░███
					░░███     ░░█████████  █████   █████
					 ░░░       ░░░░░░░░░  ░░░░░   ░░░░░


				   <>+<>                 //////      __v__        __\/__
	   `\|||/'     /---\     """""""    | _ ^ |     (_____)   .__/ ^  _ \__.
		(q p)     | o o |   <^-@-@-^>  (| o O |)    .(o o),   |\| (o)(o) |/|
	_ooO_<_>_Ooo_ooO_U_Ooo_ooO__v__Ooo_ooO_u_Ooo_ooO__(_)__Ooa__oOO_()_OOo___
	[_____}_____!____.}_____{_____|_____}_____i____.}_____!_____{_____}_____]
	__.}____.|_____{_____!____.}_____|_____{.____}_____|_____}_____|_____!___
	[_____{_____}_____|_____}_____i_____}_____|_____}_____i_____{_____}_____]

********************************************************************************

Author: Ran Aharon Cohen
Date: 7/4/22
Reviewed By: Roee Kishon🤧️

********************************************************************************

DESCRIPTION:

Attributes and policy:

--------------------------------------------------------------------------------

Operations on VSA:

*******************************************************************************/

#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
								 Typedefs
*******************************************************************************/

typedef struct block_header vsa_t;
/*each alloc, saves the amount of bytes allocated in the word right before the
adress returned to the user */

/*******************************************************************************
								Operations
*******************************************************************************/

/*
requirments:
- alloc always aligned
- use first-fit method in alloc
- defragmentation in alloc and largest.
*/

vsa_t *VSAInit(void *m_pool, size_t pool_size);
/*
Complexity: O(1)
Create the VSA
There is a minimum size: 50 * WORD_SIZE
NULL if doesn't work
*/

void *VSAAlloc(vsa_t *vsa, size_t n_bytes);
/*
Complexity: O(n)
Allocate nbytes in the given vsa.

NOTES:
- Use metadata (in WORD_SIZE) before each memory block. The metadata tells:
	1. If the block is free or not.
	2. The block size
	(Both of them in one variable)
- Use first fit method
- Do defragmentation untill you have first fit.
*/

void VSAFree(void *block);
/* Complexity: O(1)

The function frees the memory space pointed to by block
If free(block) has already been called before, undefined behavior occurs.
If block is NULL, no operation is performed.

impl: Just change the metadata to represent free space
(implemented like free)
*/

size_t VSALargestFreeBlock(vsa_t *vsa);
/*
Complexity: O(n)
Return the size of the largest available block in bytes

NOTE:
- Do defragmentation.
*/

#endif /* __VSA_H__ */
