/************************************************
 *Name: Ran Aharon Cohen                         *
 *Reviewer: Osher                                     *
 *Date: 04.07.22                                 *
 *File: mt_counting_sort.c                       *
 ************************************************/
#include <stdio.h>	  /* printf */
#include <pthread.h>  /* threads funcs */
#include <stdatomic.h>/* atomic vars */
#include <stdlib.h>	  /* malloc, calloc*/
#include <assert.h>	  /* assert */
#include <string.h>	  /* memcpy */

#include "mt_counting_sort.h" /* multi threaded counting-sort API */

/********************************  Defines  ************************************/
#define ASCII_SIZE (256)
#define FREE(ptr) \
	free(ptr);    \
	ptr = NULL
#define RETURN_IF_ERROR(is_good, error_msg) \
	if (0 == is_good)                       \
	{                                       \
		perror(error_msg);                  \
		return 1;                           \
	}

#define RETURN_AND_FREE_IF_ERROR(is_good, ptr, error_msg) \
	if (0 == is_good)                                     \
	{                                                     \
		perror(error_msg);                                \
		FREE(ptr);                                        \
		return 1;                                         \
	}
/********************************  Enums  ************************************/

enum status
{
	SUCCESS = 0,
	FALSE = 0,
	FAILURE = 1,
	TRUE = 1
};

/********************************  Structs  ************************************/

typedef struct thread_data
{
	atomic_size_t len;
	unsigned char *offset;
} thread_data_t;

/********************************  Globals  ************************************/

static const size_t g_usgn_int_size = sizeof(unsigned int);
static const size_t g_usgn_char_size = sizeof(unsigned char);

/*****************************  Static funcs  *******************************/

static void *CountLetters(void *args);
static thread_data_t *CreateThreadData(size_t len_per_th, unsigned char *offset);
static void AggregateHistogram(unsigned int *hist, int range);
static void SortByHist(unsigned char *arr, unsigned char *temp_arr,
					   size_t length, unsigned int *hist);
static void ThreadsHandler(unsigned int *letters_lut, unsigned char *arr,
						   size_t len, size_t threads_amount);

/*****************************  Implementation  *********************************/

int MtCountingSort(unsigned char *arr, size_t len, size_t threads_amount)
{
	unsigned int letters_lut[ASCII_SIZE] = {0};
	unsigned char *auxiliary_arr = NULL;

	assert(NULL != arr);

	ThreadsHandler(letters_lut, arr, len, threads_amount);

	auxiliary_arr = calloc(len + 1, g_usgn_char_size);
	if (NULL != auxiliary_arr)
	{
		return FAILURE;
	}

	AggregateHistogram(letters_lut, ASCII_SIZE);
	SortByHist(arr, auxiliary_arr, len, letters_lut);
	memcpy(arr, auxiliary_arr, len * g_usgn_char_size);

	FREE(auxiliary_arr);

	return SUCCESS;
}

static void ThreadsHandler(unsigned int *letters_lut, unsigned char *arr,
						   size_t len, size_t threads_amount)
{
	pthread_t *IDs = NULL;
	unsigned int *retval = NULL;
	thread_data_t **th_datas = NULL;
	size_t len_per_th = len / threads_amount;
	size_t len_remainder = len % threads_amount;
	static size_t curr_point = 0;
	size_t index = 0;
	size_t jndex = 0;

	IDs = calloc(threads_amount, sizeof(pthread_t));
	RETURN_IF_ERROR(NULL != IDs, "clloc failed for thread ids\n ");

	for (index = 0; index < threads_amount; ++index)
	{
		if (index == (threads_amount - 1))
		{
			len_per_th += len_remainder;
		}

		th_datas[index] = CreateThreadData(len_per_th, arr + curr_point);
		if (SUCCESS != pthread_create(&IDs[index], NULL, &CountLetters, th_datas[index]))
		{
			return FAILURE;
		}
		curr_point += len_per_th;
	}

	for (index = 0; index < threads_amount; ++index)
	{
		pthread_join(IDs[index], (void *)&retval);
		for (jndex = 0; jndex < ASCII_SIZE; ++jndex)
		{
			letters_lut[jndex] += retval[jndex];
		}
		free(retval);
	}

	FREE(IDs);
	for (index = 0; index < threads_amount; ++index)
	{
		free(th_datas[index]);
	}
	FREE(th_datas);
}

static void *CountLetters(void *args)
{
	size_t i = 0;
	unsigned int *temp_lut = calloc(ASCII_SIZE, g_usgn_int_size);
	if (NULL == temp_lut)
	{
		return NULL;
	}

	for (i = 0; i < ((thread_data_t *)args)->len; ++i)
	{
		++temp_lut[((thread_data_t *)args)->offset[i]];
	}

	return temp_lut;
}

static thread_data_t *CreateThreadData(size_t len_per_th, unsigned char *offset)
{
	thread_data_t *td;

	td = malloc(sizeof(thread_data_t));
	if (NULL == td)
	{
		return NULL;
	}

	td->len = len_per_th;
	td->offset = offset;

	return td;
}

static void AggregateHistogram(unsigned int *hist, int range)
{
	int i = 0;

	for (i = 0; i < (range - 1); ++i)
	{
		hist[i + 1] += hist[i];
	}
}

static void SortByHist(unsigned char *arr, unsigned char *temp_arr,
					   size_t length, unsigned int *hist)
{
	long i = 0;
	int index = 0;

	for (i = (long)length - 1; i >= 0; --i)
	{
		index = --hist[arr[i]];
		temp_arr[index] = arr[i];
	}
}
