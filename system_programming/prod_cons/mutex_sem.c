/************************************************
*Name: Ran Aharon Cohen                              *
*Reviewer:                                      *
*Date: 18.06.22                                 *
*File: mutex_sem.c                              *
************************************************/
#include <stdio.h>/* printf */
#include <pthread.h>/* threads funcs */
#include <stdatomic.h>/* atomic vars */
#include <semaphore.h>/* semaphore API */

#include "../../ds/include/slinked.h" /* linked list API */

#define NUM_OF_THREADS (20)
 
enum status
{
	SUCCESS = 0,
	FALSE = 0,
	FAILURE = 1,
	TRUE = 1
};

static s_linked_list_t *list = NULL;
pthread_mutex_t sll_mutex;
static atomic_int g_buff[10] = {1,2,3,4,5,6,7,8,9,10};
static atomic_int g_result[10] = {0};
static sem_t sem_read;
static atomic_int i = 0;
static atomic_int j = 0;

void *Producer(void *var)
{
	s_list_iter_t iter = NULL;

	pthread_mutex_lock(&sll_mutex);
	iter = SLinkedListBegin((s_linked_list_t *)var);
	SLinkedListInsertBefore(iter , &g_buff[i]);
	++i;
	printf("Prod %d\n",i);
	sem_post(&sem_read);
	pthread_mutex_unlock(&sll_mutex);
	
	
	return NULL;
}

void *Consumer(void *var)
{	
	s_list_iter_t iter = NULL;
	
	sem_wait(&sem_read);
	pthread_mutex_lock(&sll_mutex);
	iter = SLinkedListBegin((s_linked_list_t *)var);
	g_result[j] = *(int *)SLinkedListGetData(iter);
	SLinkedListRemove(SLinkedListBegin((s_linked_list_t *)var));
	++j;
	printf("Cons %d\n",j);
	pthread_mutex_unlock(&sll_mutex);
	
	return NULL;
}

int Init()
{
	pthread_t IDs[NUM_OF_THREADS] = {0};
	size_t index = 0;
	pthread_mutex_init(&sll_mutex, NULL);
	list = SLinkedListCreate();
	
	if (SUCCESS != sem_init(&sem_read, 0, 0))
	{
		printf("Failure in sem init");
		return 1;
	}
	
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
	sem_destroy(&sem_read);
	
	return 0;
}

int main()
{
	Init();
	
	return 0;
}
