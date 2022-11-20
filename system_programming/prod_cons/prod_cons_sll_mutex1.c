/************************************************
*Name: Ran Aharon Cohen                              *
*Reviewer: Karen                                     *
*Date: 18.06.22                                 *
*File: prod_cons_sll_mutex.c                              *
************************************************/
#include <stdio.h>/* printf */
#include <pthread.h>/* threads funcs */
#include <stdatomic.h>/* atomic vars */
#include <time.h>/* for nano sleep */

#include "../../ds/include/slinked.h" /* linked list API */

#define NUM_OF_THREADS (20)
 
enum status
{
	SUCCESS = 0,
	FALSE = 0,
	FAILURE = 1,
	TRUE = 1
};

static s_linked_list_t *list = NULL; /* if global, add g_ */
pthread_mutex_t sll_mutex;/* if global, add g_ */
static int g_buff[10] = {1,2,3,4,5,6,7,8,9,10};
static atomic_int g_result[10] = {0};
atomic_int g_i = 0;
atomic_int g_j = 0;

void *Producer(void *var)
{
	s_list_iter_t iter = NULL;
	
	pthread_mutex_lock(&sll_mutex);
	
	iter = SLinkedListBegin((s_linked_list_t *)var);
	SLinkedListInsertBefore(iter , &g_buff[g_i]);
	++g_i;
	pthread_mutex_unlock(&sll_mutex);
	
	return NULL;
}

void *Consumer(void *var)
{
	s_list_iter_t iter = NULL;
	struct timespec req = {0,0}; /*{0, 1000000} */
	struct timespec rem = {0,0};
	/*int flag = 1*/
	req.tv_nsec = 10000000; /* can move this to the initialization at line 48 , change to 1000000*/
	 /* assert */
	while(1) /*while(flag)*/
	{
		pthread_mutex_lock(&sll_mutex);
		if(!SLinkedListIsEmpty((s_linked_list_t *)var))
		{
			iter = SLinkedListBegin((s_linked_list_t *)var);
			g_result[g_j] = *(int *)SLinkedListGetData(iter);
			SLinkedListRemove(SLinkedListBegin((s_linked_list_t *)var));
			++g_j;
			pthread_mutex_unlock(&sll_mutex); /*delete this */
			break; /* can add flag to avoid repeating the same code lines 61 & 65 */
			/*flag = 0; */
		}
		pthread_mutex_unlock(&sll_mutex);
		nanosleep(&req, &rem);
	}
	
	return NULL;/*why NULL and not var? */
}

int Init()
{
	pthread_t IDs[NUM_OF_THREADS] = {0};
	size_t index = 0;

	list = SLinkedListCreate();
	
	for(index = 0; index < NUM_OF_THREADS; ++index)
	{
		if(0 == index % 2)
		{		
			if(SUCCESS != pthread_create(&IDs[index], NULL, Producer, list))
			{
				printf("didn't create thread 1\n");
				return FAILURE;
			}
		}
		else
		{		
			if(SUCCESS != pthread_create(&IDs[index], NULL, Consumer, list))
			{
				printf("didn't create thread 2\n");
				return FAILURE;
			}
		}
	}
	
	for(index = 0; index < NUM_OF_THREADS; ++index)
	{
		pthread_join(IDs[index], NULL);
	}
	
	
	for(index = 0; index < 10; ++index)
	{
		printf("res: %d\n", g_result[index]);
	}
	
	pthread_mutex_destroy(&sll_mutex);
	SLinkedListDestroy(list);
	
	return 0;
}

int main()
{
	Init();
	
	return 0;
}
