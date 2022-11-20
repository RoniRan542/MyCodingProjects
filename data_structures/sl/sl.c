/*********************************************************************
*Name : Ran Aharon Cohen	 							     		 *
*Reviewar: 🐕️ May Sohatchevzzki 🤯️									 *
*Date:  03/22/22													 *												 
*Description : 	sorted list 										 *
**********************************************************************/

#include <assert.h>/* assert */
#include <stdlib.h>/* malloc, free*/

#include "sl.h" /* 
sorted list header for definitions:
								- sl_t
								- sl_iterator_t
								- sl_cmp_func_t
								- sl_is_match_func_t
								- sl_action_func_t
*/

#define FOUND 0

static sl_iterator_t Search(const sl_t *sl, sl_iterator_t iter, const void *data);

int CheckIfSameList(sl_iterator_t from, sl_iterator_t to);

struct sl
{
    dll_list_t *list;
    sl_cmp_func_t cmp_func;
    void *param;
};

sl_t *SLCreate(sl_cmp_func_t cmp_func, void *param)
{
	sl_t *sl = NULL;
	assert(NULL != cmp_func);
	
	sl = (sl_t *)malloc(sizeof(sl_t)); 
	if(NULL == sl)
	{
		return NULL;
	}	
	
	sl->list = DLLCreate();
	if(NULL == sl->list)
	{
		free(sl);
		sl = NULL;
		return NULL;
	}	
	
	sl->param = param;
	sl->cmp_func = cmp_func;
	
	return sl;
}

void SLDestroy(sl_t *sl)
{
	assert(NULL != sl);
	
	DLLDestroy(sl->list);
	sl->list = NULL;
	free(sl);
	sl = NULL;
}

int SLIsEmpty(const sl_t *sl)
{
	assert(NULL != sl);
	
	return DLLIsEmpty(sl->list);
}

size_t SLCount(const sl_t *sl)
{
	assert(NULL != sl);
	
	return DLLCount(sl->list);
}

sl_iterator_t SLInsert(sl_t *sl, void *data)
{
	sl_iterator_t to = NULL;
	sl_iterator_t from = NULL;
	sl_iterator_t insert = NULL;
	
	assert(NULL != sl);
	assert(NULL != data);
	
	to = SLEnd(sl);
	from = SLBegin(sl);

	while(!SLIsIterEqual(from,to))
	{
		if(0 < sl->cmp_func(data, SLGetData(from), sl->param))
		{
			insert = DLLInsertBefore(from,data);
			
			return insert;
		}
		from = SLNext(from);
	}
	
	return DLLInsertBefore(from,data);
	
}

int SLForEach(sl_action_func_t action_func, void *param, 
						const sl_iterator_t from, const sl_iterator_t to)
{
	assert(NULL != action_func);
	assert(NULL != to);
	assert(NULL != from);
	
	return DLLForEach(action_func, param, from, to);	
}

sl_iterator_t SLFindIf(sl_is_match_func_t is_match, void *param, 
					const sl_iterator_t from, const sl_iterator_t to)
{
	assert(NULL != to);
	assert(NULL != from);
	assert(NULL != is_match);
	
	return DLLFindMatch(is_match, param, from, to);	
}

sl_iterator_t SLFind(const sl_t *sl, const sl_iterator_t from,
 					 const sl_iterator_t to, const void *data)
{
	sl_iterator_t runner = from;
	
	assert(NULL != sl);
	assert(NULL != to);
	assert(NULL != from);
	
	while(!SLIsIterEqual(runner,to))
	{
		if(FOUND == sl->cmp_func(data, SLGetData(runner), sl->param))
		{	
			return runner;
		}
		
		runner = SLNext(runner);
	}
	
	return to;	
}

sl_iterator_t SLRemove(sl_iterator_t where)
{
	assert(NULL != where);
	
	return DLLRemove(where);
}

sl_iterator_t SLBegin(const sl_t *sl)
{
	assert(NULL != sl);
	
	return DLLBegin(sl->list);
}

sl_iterator_t SLEnd(const sl_t *sl)
{
	assert(NULL != sl);
	
	return DLLEnd(sl->list);
}

int SLIsIterEqual(const sl_iterator_t iter1, const sl_iterator_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

sl_iterator_t SLNext(const sl_iterator_t iter)
{
	assert(NULL != iter);
	
	return DLLNext(iter);
}

sl_iterator_t SLPrev(const sl_iterator_t iter)
{
	assert(NULL != iter);
	
	return DLLPrev(iter);
}

void *SLGetData(const sl_iterator_t iter)
{
	assert(NULL != iter);
	
	return DLLGetData(iter);
}

void *SLPopFront(sl_t *sl)
{
	assert(NULL != sl);
	
	return DLLPopFront(sl->list);
}

void *SLPopBack(sl_t *sl)
{
	assert(NULL != sl);
	
	return DLLPopBack(sl->list);
}

sl_t *SLMerge(sl_t *dest, sl_t *src)
{
	sl_iterator_t iter_dest = NULL;
	sl_iterator_t to_src = NULL;
	
	assert(NULL != dest);
	assert(NULL != src);
	assert(dest->cmp_func == src->cmp_func);
	#ifdef NDBUG
	assert(CheckIfSameList(SLBegin(dest),SLBegin(src)));
	#endif
	iter_dest = SLBegin(dest);
	to_src = SLBegin(src);
	
	while(!SLIsEmpty(src))
	{
		iter_dest = Search(dest, iter_dest, SLGetData(SLBegin(src)));
		if(NULL == SLNext(iter_dest))
		{
			to_src = SLEnd(src);
		}
		else
		{
			to_src = Search(src, SLBegin(src), SLGetData(iter_dest));
		}
		
		DLLSplice(iter_dest, SLBegin(src), to_src);
	}
	
	return dest;
}


static sl_iterator_t Search(const sl_t *sl, sl_iterator_t iter, const void *data)
{
	sl_iterator_t sl_end = NULL;
	sl_iterator_t runner = NULL;
	
	assert(NULL != iter);
	assert(NULL != sl);
	assert(NULL != data);
	
	sl_end = SLEnd(sl);
	runner = iter;
	
	while(!SLIsIterEqual(runner,sl_end) && 
		0 >= sl->cmp_func(data, SLGetData(runner), sl->param))
	{
		runner = SLNext(runner);
	}
	
	return runner;
}


int CheckIfSameList(sl_iterator_t from, sl_iterator_t to)
{
	while ((from != to) && (NULL != from))
	{
		from = SLNext(from);
	}

	return (from == to);
}


