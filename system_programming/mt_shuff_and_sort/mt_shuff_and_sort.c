/********************************************
 *Name: Ran Aharon Cohen                         *
 *Reviewer:                                      *
 *Date: 06.07.22                                 *
 *File: mt_shuff_and_sort.c                      *
 ************************************************/
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>/* qsort, malloc, calloc, free */
#include <string.h>/* strcmp */
#include <time.h>
#include <stdatomic.h>
#include <pthread.h>/* pthread_create */
#include <assert.h> /* assert */

#define FREE(ptr) \
	free(ptr);    \
	ptr = NULL

#define RETURN_IF_ERROR(is_good, error_msg) \
	if (0 == is_good)                       \
	{                                       \
		perror(error_msg);                  \
		return 1;                           \
	}

#define N_COPIES (50)
#define THREADS_AMOUNT (2)
#define SHUFF_TIMES (50)
#define DICT_LEN (N_COPIES * g_nwords)

enum return_status
{
	ERROR = -1,
	SUCCESS = 0,
	FAILURE
};

/*************************      typdefs & struct      *********************************/
typedef unsigned char UC;
typedef void *(*thread_func_t)(void *arg);
typedef int (*s_cmp_func_t)(const void *, const void *);

typedef struct thread_data
{
	atomic_size_t len;
	unsigned char **offset;
} thread_data_t;

/*************************      Globals      *********************************/

static const size_t g_char_size = sizeof(char);
static const size_t g_char_ptr_size = sizeof(char *);
static size_t g_nwords = 0;

/*************************      Static Funcs      *********************************/

static int CompareFunc(const void *v1, const void *v2);
static int RandFunc(const void *v1, const void *v2);
static UC *CreateBigData();
static void *CreateMultyArrayOfPtrs(unsigned char *buffer);
static void ShuffDict(unsigned char **dict);
static int SortDictMultyThreads(unsigned char **dict);
static void *SortSection(void *arg);
static void SortAll(unsigned char **dict);
static void FillWordsArr(unsigned char **words_arr, unsigned char *dictionary);
static void DivideDictionary(unsigned char *dictionary);
void QuickSort(void *arr, size_t num_elems, size_t elem_size, s_cmp_func_t cmp);
static void Swap(char *dataX, char *dataY, size_t elem_size);
static void *SortQuick(void *arg);

/*************************      Static lut      *********************************/
static thread_func_t g_thread_func_lut[2] = {&SortSection, &SortQuick};

/*************************      Implementation      *********************************/

int main()
{
	struct timespec start, end;
	float realtime = 0;
	unsigned char **multi_ptr_array = NULL;
	unsigned char *buffer = NULL;

	srand(time(NULL));
	buffer = CreateBigData();
	multi_ptr_array = CreateMultyArrayOfPtrs((unsigned char *)buffer);
	ShuffDict(multi_ptr_array);

	clock_gettime(CLOCK_REALTIME, &start);
	SortDictMultyThreads(multi_ptr_array);

	SortAll(multi_ptr_array);

	clock_gettime(CLOCK_REALTIME, &end);
	realtime = (end.tv_sec - start.tv_sec) +
			   (end.tv_nsec - start.tv_nsec) / 1000000000.0;

	printf("it took %f to sort with %d threads\n", realtime, THREADS_AMOUNT);

	free(multi_ptr_array);
	multi_ptr_array = NULL;
	free(buffer);
	buffer = NULL;

	return SUCCESS;
}

static UC *CreateBigData()
{
	FILE *infile = NULL;
	unsigned char *buffer = NULL;
	long numbytes = 0;
	unsigned char ch = 0;

	infile = fopen("/usr/share/dict/words", "r");
	if (infile == NULL)
	{
		return NULL;
	}

	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);
	fseek(infile, 0L, SEEK_SET);

	buffer = (unsigned char *)calloc(numbytes, g_char_size);
	if (buffer == NULL)
	{
		printf(" malloc failed");
		return NULL;
	}

	fread(buffer, sizeof(unsigned char), numbytes, infile);
	fseek(infile, 0L, SEEK_SET);
	while (!feof(infile))
	{
		ch = fgetc(infile);

		if (ch == '\n')
		{
			g_nwords++;
		}
	}

	fclose(infile);

	return buffer;
}

static int SortDictMultyThreads(unsigned char **dict)
{
	pthread_t *IDs = NULL;

	size_t len_per_th = DICT_LEN / THREADS_AMOUNT;
	size_t len_remainder = DICT_LEN % THREADS_AMOUNT;
	static size_t curr_point = 0;
	size_t index = 0;
	thread_data_t **tds = NULL;

	tds = calloc(THREADS_AMOUNT, sizeof(thread_data_t));
	RETURN_IF_ERROR((NULL != tds), "calloc failed for thread datas\n ");
	IDs = calloc(THREADS_AMOUNT, sizeof(pthread_t));
	RETURN_IF_ERROR((NULL != IDs), "calloc failed for thread ids\n ");

	for (index = 0; index < THREADS_AMOUNT; ++index)
	{
		if (index == (THREADS_AMOUNT - 1))
		{
			len_per_th += len_remainder;
		}

		tds[index] = malloc(sizeof(thread_data_t));
		RETURN_IF_ERROR((NULL != tds[index]), "calloc failed for thread datas\n ");
		tds[index]->len = len_per_th;
		tds[index]->offset = dict + curr_point;
		if (SUCCESS != pthread_create(&IDs[index], NULL, g_thread_func_lut[1], tds[index]))
		{
			return FAILURE;
		}
		curr_point += len_per_th;
	}

	for (index = 0; index < THREADS_AMOUNT; ++index)
	{
		pthread_join(IDs[index], NULL);
	}

	FREE(IDs);

	return SUCCESS;
}

static void *SortSection(void *arg)
{
	size_t size = ((thread_data_t *)arg)->len;

	qsort(((thread_data_t *)arg)->offset, size, g_char_ptr_size, &CompareFunc);

	return NULL;
}

static void *SortQuick(void *arg)
{
	size_t size = ((thread_data_t *)arg)->len;

	QuickSort(((thread_data_t *)arg)->offset, size, g_char_ptr_size, &CompareFunc);

	return NULL;
}

static void SortAll(unsigned char **dict)
{
	qsort(dict, g_nwords * N_COPIES, g_char_ptr_size, &CompareFunc);
}

static void ShuffDict(unsigned char **dict)
{
	size_t i = 0;

	for (i = 0; i < SHUFF_TIMES; ++i)
	{
		qsort(dict, g_nwords * N_COPIES, g_char_ptr_size, &RandFunc);
	}
}

static int RandFunc(const void *v1, const void *v2)
{
	(void)v1;
	(void)v2;
	return (rand() % 3) - 1;
}

static int CompareFunc(const void *v1, const void *v2)
{
	return strcmp(*(char **)v1, *(char **)v2);
}

static void *CreateMultyArrayOfPtrs(unsigned char *buffer)
{
	size_t i = 0;
	unsigned char **multi_ptr_array = NULL;

	multi_ptr_array = (unsigned char **)malloc(g_nwords * N_COPIES * g_char_ptr_size);
	if (NULL == multi_ptr_array)
	{
		return NULL;
	}

	DivideDictionary(buffer);

	for (i = 0; i < N_COPIES; ++i)
	{
		FillWordsArr(multi_ptr_array + (i * g_nwords), buffer);
	}

	return multi_ptr_array;
}

static void DivideDictionary(unsigned char *dictionary)
{
	assert(NULL != dictionary);

	while (NULL != dictionary)
	{
		while ('\n' != *dictionary && '\0' != *dictionary)
		{
			++dictionary;
		}
		if ('\0' == *dictionary)
		{
			break;
		}
		else if ('\n' == *dictionary)
		{
			*dictionary = '\0';
			++dictionary;
		}
	}
}

static void FillWordsArr(unsigned char **words_arr, unsigned char *dictionary)
{
	unsigned char *str = NULL;
	size_t i = 0;

	assert(NULL != words_arr);
	assert(NULL != dictionary);
	for (i = 0; i < g_nwords; i++)
	{
		str = dictionary;
		while ('\0' != *dictionary)
		{
			++dictionary;
		}

		if ('\0' == *dictionary)
		{
			*words_arr = str;
			++dictionary;
			++words_arr;
		}
	}
}

void QuickSort(void *arr, size_t num_elems, size_t elem_size, s_cmp_func_t cmp)
{
	char *left = NULL, *right = NULL, *pivot = NULL;
	size_t left_num_elems = 0;
	assert(NULL != arr);
	assert(NULL != cmp);

	if (1 >= num_elems)
	{
		return;
	}

	left = (char *)arr;
	pivot = (char *)arr + ((num_elems - 1) * elem_size);
	right = pivot - elem_size;

	while (left <= right)
	{
		if (0 < cmp(pivot, left))
		{
			left += elem_size;
		}
		else
		{
			Swap(left, right, elem_size);
			Swap(pivot, right, elem_size);
			pivot = right;
			right = pivot - elem_size;
		}
	}

	left_num_elems = (pivot - (char *)arr) / elem_size;
	QuickSort(arr, left_num_elems, elem_size, cmp);
	QuickSort(pivot + elem_size, (num_elems - left_num_elems - 1), elem_size, cmp);
}

static void Swap(char *dataX, char *dataY, size_t elem_size)
{
	char temp = 0;
	size_t i = 0;

	assert(NULL != dataX);
	assert(NULL != dataY);

	for (i = 0; i < elem_size; ++i)
	{
		temp = *dataX;
		*dataX = *dataY;
		*dataY = temp;

		++dataX;
		++dataY;
	}
}
