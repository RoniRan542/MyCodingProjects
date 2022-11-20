/*******************************************************************************
*Name: Ran Aharon Cohen									 			 
*Reviewer: 	Daniel									 			 
*Date: 05/16/22													 			 
*ht.c														 			 
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdlib.h>/* malloc */
#include <assert.h>/* assert */

#include "dll.h"/* for doubly linked-list funcs */
#include "ht.h"/* for hash funcs */

#define FREE(var) free(var);\
                    var = NULL;
struct ht
{	
	ht_hash_func_t ht_func;
	void *ht_param;
	ht_cmp_func_t cmp;
	void *cmp_param;
	size_t entries;
	dll_list_t **buckets;
};

typedef struct find
{
    ht_cmp_func_t cmp;
    void *cmp_param;
    void *to_find;
}find_t;

enum status
{
	SUCCESS = 0,
	FALSE = 0,
	FAILURE = 1,
	TRUE = 1
};

static dll_list_t *GetBucket(ht_t *ht, void *data);
static void FreeBucketsUpTo(dll_list_t **buckets, size_t to);
static int InitTableEntries(dll_list_t **buckets, size_t entries);
static dll_iterator_t GetMatchedIter(ht_t *ht, void *data);

ht_t *HTCreate(ht_hash_func_t ht_func, void *ht_param, ht_cmp_func_t cmp, 
															void *cmp_param,  size_t entries)
{
	ht_t *hash = NULL;
	int init = 0;
	
	assert(NULL != ht_func);
	assert(NULL != cmp);
	assert(NULL != ht_param);
	
	hash = (ht_t *)malloc(sizeof(ht_t));
	if(NULL == hash)
	{
		return NULL;
	}
	
	hash->buckets = (dll_list_t **)malloc(sizeof(dll_list_t *)* entries);
	init = InitTableEntries(hash->buckets, entries);
	if(NULL == hash->buckets || FAILURE == init)
	{
		FREE(hash->buckets);
		FREE(hash);
		return NULL;
	}
	  
	hash->ht_func = ht_func;
	hash->ht_param = ht_param;
	hash->cmp = cmp;
	hash->cmp_param = cmp_param;
	hash->entries = entries;
	
	return hash;
}

static int InitTableEntries(dll_list_t **buckets, size_t entries)
{
	size_t i = 0;
	
	assert(NULL != buckets);
	
	for(i = 0; i < entries; ++i)
	{
		*(buckets + i) = DLLCreate(); 
		if(NULL == *(buckets + i))
		{
			FreeBucketsUpTo(buckets, i);
			
			return FAILURE;
		}
	}
	
	return SUCCESS;
}

static void FreeBucketsUpTo(dll_list_t **buckets, size_t to)
{
	size_t i = 0;
	
	assert(NULL != buckets);
	
	for(i = 0; i < to; ++i)
	{
		DLLDestroy(buckets[i]);
	}
}

void HTDestroy(ht_t *ht)
{
	assert(NULL != ht);
	
	FreeBucketsUpTo(ht->buckets,ht->entries);
	
	FREE(ht->buckets);
	FREE(ht);
}

int HTInsert(ht_t *ht, void *data)
{
	dll_list_t *bucket = NULL;
	
	assert(NULL != ht);
	assert(NULL != data);
	
	bucket = GetBucket(ht, data);
	
	return DLLPushBack(bucket, data);
}

static int IsMatch(const void *data, void *param)
{
    find_t *find = (find_t *)param;
    
    return !find->cmp(data, find->to_find, find->cmp_param);
}

void HTRemove(ht_t *ht, void *data)
{
    dll_iterator_t result = NULL;
    
    assert(NULL != ht);
    
    result = GetMatchedIter(ht, data);
    if(result != NULL)
    {
    	 DLLRemove(result);
    }
}

size_t HTSize(const ht_t *ht)
{
	size_t i = 0;
	size_t result = 0;
	
	assert(NULL != ht);
	
	for(i = 0; i < ht->entries; ++i)
	{
		result += DLLCount(ht->buckets[i]);
	}
	
	return result;
}

void *HTFind(ht_t *ht, void *data)
{
   	dll_iterator_t result = NULL;
   	
    assert(NULL != ht);
    
    result = GetMatchedIter(ht, data);
    if(NULL == result)
    {
    	return NULL;
    }
    
	return DLLGetData(result);
}

static dll_iterator_t GetMatchedIter(ht_t *ht, void *data)
{
	find_t find;
   	dll_list_t *bucket = NULL;
   	dll_iterator_t result = NULL;
   	
    assert(NULL != ht);
    
	bucket = GetBucket(ht, data);
    find.cmp = ht->cmp;
    find.cmp_param = ht->cmp_param;
    find.to_find = data;
    
    result = DLLFindMatch(IsMatch, &find, DLLBegin(bucket),DLLEnd(bucket));
    if(DLLIsIterEqual(DLLEnd(bucket), result))
    {
    	return NULL;
    }
    
    return result;
}

static dll_list_t *GetBucket(ht_t *ht, void *data)
{
	size_t key = 0;
	size_t index = 0;
	
	key = ht->ht_func(data, ht->ht_param);
	index = key % ht->entries;

	return ht->buckets[index];
}

int HTIsEmpty(const ht_t *ht)
{
	size_t result = 0;
	size_t i = 0;
	
	assert(NULL != ht);
	
	for(i = 0; i < ht->entries && 0 == result; ++i)
	{
		result += !DLLIsEmpty(ht->buckets[i]);
	}
	
	return !result;
}

int HTForEach(ht_t *ht, ht_action_func_t act, void *action_param)
{
	size_t i = 0;
	int status = 0;
	
	assert(NULL != ht);
	assert(NULL != act);
	
	for(i = 0; i < ht->entries && SUCCESS == status ; ++i)
	{
		status = DLLForEach(act, action_param, DLLBegin(ht->buckets[i]), DLLEnd(ht->buckets[i]));						
	}
	
	return status;
}

