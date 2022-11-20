/*******************************************************************************
		   _\_   				   _\_					       _\_      
		\\/  o\					\\/  o\						\\/  o\		
		//\___=					//\___=						//\___=


					oooooooooooo  .oooooo..o       .o.       
          O  		`888'     `8 d8P'    `Y8      .888.      o   _/,_
   _\_   o			 888         Y88bo.          .8"888.      . /o...\__//
\\/  o\ .			 888oooo8     `"Y8888o.     .8' `888.       \_'__/``\`
//\___=				 888    "         `"Y88b   .88ooo8888.   	  \`
   ''				 888         oo     .d8P  .8'     `888.  
					o888o        8""88888P'  o88o     o8888o 

		 O
		o   _/,_			 		 _/,_					   _\_   o   
		 . /o...\__//				/o...\__//				\\/  o\ .		
		   \_'__/``\`				\_'__/``\`				//\___=
		     \`						  \`

********************************************************************************

		   _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._
		 ,'_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._`.
		( (                                                         ) )
		 ) )                                                       ( (
		( (              Author: Ran Aharon Cohen			        ) )
		 ) )             Date: 3/4/22                              ( (
		( (              Reviewed By:                               ) )
		 ) )                                                       ( (
		( (_.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._) )
		 `._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._,'


********************************************************************************
DESCRIPTION: 
Fixed Size Allocators (aka FSA) memory are used to solve at least two types of 
memory related problems. First, global heap allocations/deallocations can be 
slow and nondeterministic. You never know how long the memory manager is going 
to take. Secondly, to eliminate the possibility of a memory allocation fault 
caused by a fragmented heap – a valid concern, especially on mission-critical 
type systems.

Attributes and policy:
- 

--------------------------------------------------------------------------------

Operations on FSA:
- 

*******************************************************************************/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

/*******************************************************************************
                                 Typedefs
*******************************************************************************/

typedef struct fsa fsa_t;

/*******************************************************************************
                                 Operations
*******************************************************************************/

/* Note: In case of wrong reference, undefined behavior occurs.
for example sending the wrong pool, sending block that already was free */

size_t FSAReqPoolSize(size_t nblocks, size_t block_size);
/* O(1) */

fsa_t *FSAInit(void *mem_pool, size_t nblocks, size_t block_size);
/* O(n) */

size_t FSACountFreeBlocks(const fsa_t *pool);
/* O(n) */

void *FSAAlloc(fsa_t *pool);
/* O(1) 
In case of failure, return NULL
*/

void FSAFree(fsa_t *pool, void *block); 
/* O(1) 
Notice the input comments that man of malloc (to read about free) function gives 
*/

#endif /*__FSA_H__*/

