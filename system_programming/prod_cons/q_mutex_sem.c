/************************************************
*Name: Ran Aharon Cohen                         *
*Reviewer: Karen                                *
*Date: 18.06.22                                 *
*File: q_mutex_sem.c
*Description: FSQ + mutex + 2 semaphores        *
************************************************/
#include <stdio.h>/* printf */
#include <pthread.h>/* threads funcs */
#include <stdatomic.h>/* atomic vars */
#include <semaphore.h>/* semaphore API */

#include "../../ds/include/cbuffer.h"

#define NUM_OF_THREADS (20)

enum status
{
	SUCCESS = 0,
	FALSE = 0,
	FAILURE = 1,
	TRUE = 1
};

static c_buffer_t *cbuffer = NULL;
pthread_mutex_t cq_mutex;
static atomic_int g_result[10] = {0};
static sem_t sem_prod;
static sem_t sem_cons;
static const size_t g_int_size = sizeof(int);

void *Producer(void *var)
{
	static atomic_int i = 0;
	
	sem_wait(&sem_prod);
	pthread_mutex_lock(&cq_mutex);
	i++;
	CBufferWrite((c_buffer_t *)var, &i, g_int_size);
	printf("Prod %d\n",i);
	pthread_mutex_unlock(&cq_mutex);
	sem_post(&sem_cons);
	
	return NULL;
}

void *Consumer(void *var)
{
	static atomic_int j = 0;
	
	sem_wait(&sem_cons);
	pthread_mutex_lock(&cq_mutex);
	CBufferRead((c_buffer_t *)var, &g_result[j], g_int_size);
	++j;
	printf("Cons %d\n",j);
	pthread_mutex_unlock(&cq_mutex);
	sem_post(&sem_prod);

	return NULL;
}

int Init()
{
	pthread_t IDs[NUM_OF_THREADS] = {0};
	size_t index = 0;
	
	pthread_mutex_init(&cq_mutex, NULL);
	
	if (SUCCESS != sem_init(&sem_prod, 0, 1))
	{
		printf("Failure in sem init");
		return 1;
	}
	
	if (SUCCESS != sem_init(&sem_cons, 0, 0))
	{
		printf("Failure in sem init");
		return 1;
	}


	cbuffer = CBufferCreate(10);
	
	for(index = 0; index < NUM_OF_THREADS; ++index)
	{
		if(0 == index % 2)
		{		
			if(SUCCESS != pthread_create(&IDs[index], NULL, Producer, cbuffer))
			{
				printf("didn't create thread 1\n");
				return FAILURE;
			}
		}
		else
		{		
			if(SUCCESS != pthread_create(&IDs[index], NULL, Consumer, cbuffer))
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
	
	pthread_mutex_destroy(&cq_mutex);
	sem_destroy(&sem_prod);
	sem_destroy(&sem_cons);
	CBufferDestroy(cbuffer);
	
	return 0;
}

int main()
{
	Init();
	
	return 0;
}
