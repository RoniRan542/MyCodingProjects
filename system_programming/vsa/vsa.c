/*************************************************
 *Name : Ran Aharon Cohen						 *
 *Reviewar:	Nuriel	 	    			         *
 *Date: 	09.04.22		            		 	 *
 *Description :vsa - Variable Size Allocator	     *
 **************************************************/
#include <assert.h>/* for assert*/

#include "vsa.h"

#define LAST_BLOCK (1)
#define USED_BLOCK (2)
#define MANAGER_WORD_SIZE (1)

static void Defrag(vsa_t *vsa);
static void *AllocHandler(vsa_t *vsa_block, size_t n_bytes);
static size_t AlignBlockSizeUp(size_t block_size);
static size_t AlignBlockSizeDown(size_t block_size);
static size_t GetNextBlock(vsa_t *vsa);
static int IsLastBlock(size_t meta_data);
static int IsUsedBlock(size_t meta_data);

struct block_header
{
	size_t meta_data;
};

static const size_t g_header_size = sizeof(vsa_t);
static const size_t g_align_word_size = sizeof(size_t) - 1;

vsa_t *VSAInit(void *m_pool, size_t pool_size)
{
	vsa_t *vsa_header = NULL;

	assert(NULL != m_pool);
	assert(2 * g_header_size < pool_size);

	vsa_header = (vsa_t *)m_pool;
	vsa_header->meta_data = AlignBlockSizeDown(pool_size) - g_header_size;
	vsa_header->meta_data += LAST_BLOCK;

	return vsa_header;
}

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	vsa_t *vsa_runner = vsa;
	size_t calc_jump = 0;

	assert(NULL != vsa);
	assert(0 != n_bytes);

	n_bytes = AlignBlockSizeUp(n_bytes);

	while (!IsLastBlock(vsa_runner->meta_data))
	{
		if (!IsUsedBlock(vsa_runner->meta_data))
		{
			Defrag(vsa_runner);

			if (n_bytes <= vsa_runner->meta_data)
			{
				return AllocHandler(vsa_runner, n_bytes);
			}
			vsa_runner += GetNextBlock(vsa_runner);
		}
		else
		{
			calc_jump = vsa_runner->meta_data + g_header_size - USED_BLOCK;
			vsa_runner += calc_jump / g_header_size;
		}
	}

	if (!IsUsedBlock(vsa_runner->meta_data))
	{
		if (n_bytes <= vsa_runner->meta_data)
		{
			return AllocHandler(vsa_runner, n_bytes);
		}
	}

	return NULL;
}

static size_t GetNextBlock(vsa_t *vsa)
{
	return (vsa->meta_data + g_header_size) / g_header_size;
}

static int IsLastBlock(size_t meta_data)
{
	return meta_data & LAST_BLOCK;
}

static int IsUsedBlock(size_t meta_data)
{
	return meta_data & USED_BLOCK;
}

void VSAFree(void *block)
{
	vsa_t *vsa_block = NULL;

	assert(NULL != block);

	vsa_block = (vsa_t *)block - MANAGER_WORD_SIZE;
	vsa_block->meta_data -= USED_BLOCK;
}

size_t VSALargestFreeBlock(vsa_t *vsa)
{
	size_t amount = 0;
	size_t calc_jump = 0;

	assert(NULL != vsa);

	while (!IsLastBlock(vsa->meta_data))
	{
		if (!IsUsedBlock(vsa->meta_data))
		{
			Defrag(vsa);

			if (amount < vsa->meta_data)
			{
				amount = vsa->meta_data;
			}
			if (!IsLastBlock(vsa->meta_data))
			{
				vsa += GetNextBlock(vsa);
			}
		}
		else
		{
			calc_jump = vsa->meta_data + g_header_size - USED_BLOCK;
			vsa += calc_jump / g_header_size;
		}
	}

	if (amount < vsa->meta_data && !IsUsedBlock(vsa->meta_data))
	{
		amount = vsa->meta_data;
	}

	return amount & ~LAST_BLOCK;
}

static void Defrag(vsa_t *vsa_block)
{
	vsa_t *next_block = NULL;

	assert(NULL != vsa_block);

	next_block = vsa_block + GetNextBlock(vsa_block);

	while (!IsUsedBlock(next_block->meta_data) &&
		   !IsLastBlock(next_block->meta_data))
	{
		vsa_block->meta_data += next_block->meta_data + g_header_size;
		next_block = vsa_block + GetNextBlock(vsa_block);
	}

	if (!IsUsedBlock(next_block->meta_data) &&
		IsLastBlock(next_block->meta_data))
	{
		vsa_block->meta_data += next_block->meta_data + g_header_size;
	}
}

static void *AllocHandler(vsa_t *vsa_block, size_t n_bytes)
{
	size_t temp_meta_data = 0;
	vsa_t *vsa_start = NULL;

	assert(NULL != vsa_block);

	vsa_start = vsa_block;

	if (n_bytes == (vsa_block->meta_data & ~LAST_BLOCK))
	{
		vsa_block->meta_data += USED_BLOCK;
	}
	else
	{
		temp_meta_data = vsa_block->meta_data - (n_bytes + g_header_size);
		vsa_block->meta_data = n_bytes;
		vsa_block->meta_data += USED_BLOCK;

		vsa_block += (n_bytes + g_header_size) / g_header_size;
		vsa_block->meta_data = temp_meta_data;
	}

	return vsa_start + MANAGER_WORD_SIZE;
}

static size_t AlignBlockSizeUp(size_t block_size)
{
	block_size += g_align_word_size;

	return block_size & ~g_align_word_size;
}

static size_t AlignBlockSizeDown(size_t block_size)
{
	return block_size & ~g_align_word_size;
}
