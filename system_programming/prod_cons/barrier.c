/***********************************************************************************
*Name: Ran Aharon Cohen                        									   *
*Reviewer: Karen                                  									   *
*Date: 18.06.22                                									   *
*File: q_mutex_sem.c															   *
*Description: 1 producer + multi consumers + FSQ + 1 mutex + 1 semaphore  + BARRIER*
**********************************************************************************/
#include <stdio.h>/* printf */
#include <pthread.h>/* threads funcs */
#include <stdatomic.h>/* atomic vars */
#include <semaphore.h>/* semaphore API */

#include "../../ds/include/cbuffer.h" /* circular buffer API */

#define NUM_OF_THREADS (4)
#define NUM_OF_CONS (3)

enum status
{
	SUCCESS = 0,
	FALSE = 0,
	FAILURE = 1,
	TRUE = 1
};

static c_buffer_t *cbuffer = NULL;
static pthread_mutex_t mutex;
static pthread_cond_t cv;
static atomic_int g_source[NUM_OF_CONS] = {1,2,3};
static atomic_int g_result[NUM_OF_CONS] = {1,2,3};
static sem_t sem_prod;
static const size_t g_int_size = sizeof(int);

void *Producer(void *var)
{	
	int i = 0;
	
	for(i = 0; i < NUM_OF_CONS; ++i)
	{		
		sem_wait(&sem_prod);
	}
	   
	pthread_mutex_lock(&mutex);

	for(i = 0; i < NUM_OF_CONS; ++i)
	{		
		CBufferWrite((c_buffer_t *)var, &g_source[i], g_int_size);
	}

	pthread_cond_broadcast(&cv);
	pthread_mutex_unlock(&mutex);
	
	sem_wait(&sem_prod);
	sem_wait(&sem_prod);
	sem_wait(&sem_prod);
	
	return NULL;
}

void *Consumer(void *var)
{
	static atomic_int j = 0;
	
	sem_post(&sem_prod);
	pthread_mutex_lock(&mutex);
	
	pthread_cond_wait(&cv, &mutex); 
	
	CBufferRead((c_buffer_t *)var, &g_result[j++], g_int_size);

	sem_post(&sem_prod);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

int Init()
{
	pthread_t IDs[NUM_OF_THREADS] = {0};
	size_t index = 0;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cv, NULL); 
	sem_init(&sem_prod, 0, 0);
	cbuffer = CBufferCreate(NUM_OF_CONS);
	
	for(index = 0; index < NUM_OF_THREADS; ++index)
	{
		if(0 == index)
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
	
	for(index = 0; index < NUM_OF_CONS; ++index)
	{
		printf("res: %d\n", g_result[index]);
	}
	
	pthread_mutex_destroy(&mutex);
	CBufferDestroy(cbuffer);
	sem_destroy(&sem_prod);
	
	return 0;
}

int main()
{
	Init();
	
	return 0;
}
