/*******************************************************************************
 *Name: Adiya Tayri												 			   *
 *Reviewer:  Ran Roni									 			 		   *
 *Pass Valgrind: YES														   *
 *Date: 04/07/22												 			   *
 *mt_counting_sort.c										 				   *
 ******************************************************************************/
#include <stdlib.h>       /* for printf */
#include <pthread.h>      /* for pthread_create() */
#include <time.h>         /* for time_t */
#include <unistd.h>       /* for sleep */
#include <sys/resource.h> /* for getrlimit */
#include <assert.h>       /*assert*/

#include "mt_counting_sort.h" /*mt API*/

enum Status
{
    SUCCESS,
    FAIL
};

enum WorkDivisionThreads
{
    REGULAR_THREAD = 0,
    LAST_THREAD
};

typedef struct Ranges
{
    unsigned char *arr;
    size_t size;
} range_t;


#define HISTOGRAM_SIZE (256)/* defines should be below the includes. maybe give more explicit name */

static void WorkDivisionCalc(size_t threads_amount, size_t len,
                             size_t *threads_work_division);
static int PthreadCreate(unsigned char *arr, size_t threads_amount,
                         size_t *threads_work_division, range_t *ranges);
static void *CountingSort(void *arg);
static void CalcThreadHistogram(unsigned char *arr, size_t length);
static void AddResultsToMainHistogram(int *histogram);
static void SumHistogramElem(void);
static void CopyArr(unsigned char *dest_arr, unsigned char const *src_arr,
                    size_t length);

static size_t g_histogram[HISTOGRAM_SIZE] = {0};
static pthread_mutex_t g_lock = {0};

int MtCountingSort(unsigned char *arr, size_t len, size_t threads_amount)
{
    /* this array is unnecessary, it's enuagh to use 2 variables*/
    size_t threads_work_division[2] = {0};
    range_t *ranges = {0};
    size_t i = 0;
    unsigned char *aux_arr = (unsigned char *)calloc(len, sizeof(char));

    assert(arr);/* make it more explicit: NULL != arr*/
    assert(threads_amount);/* canal */
    assert(len);/* canal */

    threads_work_division[REGULAR_THREAD] = threads_work_division[LAST_THREAD] =
        len / threads_amount;

    if (pthread_mutex_init(&g_lock, NULL) != SUCCESS)
    {
        return FAIL;
    }

    WorkDivisionCalc(threads_amount, len, threads_work_division);

    if (!(ranges = calloc(threads_amount, sizeof(range_t))))
    {
        return FAIL;
    }

    if (PthreadCreate(arr, threads_amount, threads_work_division, ranges))
    {
        return FAIL;
    }

    SumHistogramElem();

    for (i = len - 1; 0 <= (long)i; --i)
    {
        --g_histogram[arr[i]];
        aux_arr[g_histogram[arr[i]]] = arr[i];
    }

    CopyArr(arr, aux_arr, len);

    pthread_mutex_destroy(&g_lock);

    free(aux_arr);
    aux_arr = NULL;
    free(ranges);
    ranges = NULL;

    return SUCCESS;
}

static void WorkDivisionCalc(size_t threads_amount, size_t len,
                             size_t *threads_work_division)
{
    size_t regular_thread_work = 0;
    size_t last_thread_work = 0;

    assert(threads_amount);/* canal */
    assert(len);/* canal */
    assert(threads_work_division);/* canal */

    if (len % threads_amount)/* canal */
    {
        regular_thread_work = len / threads_amount + 1;
        /* more straight forward is to add the remainder to regular_thread_work:
        regular_thread_work + len % threads_amount */
        last_thread_work = len - (threads_amount - 1) * regular_thread_work;

        threads_work_division[REGULAR_THREAD] = regular_thread_work;
        threads_work_division[LAST_THREAD] = last_thread_work;
    }
}

static int PthreadCreate(unsigned char *arr, size_t threads_amount,
                         size_t *threads_work_division, range_t *ranges)
{
    size_t i = 0;
    pthread_t *threads = NULL;

    assert(arr);/* canal */
    assert(threads_amount);/* canal */
    assert(threads_work_division);/* canal */
    assert(ranges);/* canal */

    if (!(threads = (pthread_t *)calloc(threads_amount, sizeof(pthread_t))))
    {
        return FAIL;
    }

    for (i = 0; threads_amount - 1 > i; ++i)
    {
        ranges[i].arr = arr + i * threads_work_division[REGULAR_THREAD];
        ranges[i].size = threads_work_division[REGULAR_THREAD];

        if (pthread_create(&threads[i], NULL, &CountingSort, &ranges[i]))
        {
            return FAIL;
        }
    }

    ranges[i].arr = arr + i * threads_work_division[REGULAR_THREAD];
    ranges[i].size = threads_work_division[LAST_THREAD];

    if (pthread_create(&threads[i], NULL, &CountingSort, &ranges[i]))
    {
        return FAIL;
    }

    for (i = 0; threads_amount > i; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    threads = NULL;

    return SUCCESS;
}

static void *CountingSort(void *arg)
{
    range_t *ranges = (range_t *)arg;

    CalcThreadHistogram(ranges->arr, ranges->size);

    return ranges;
}

static void CalcThreadHistogram(unsigned char *arr, size_t length)
{
    int histogram[HISTOGRAM_SIZE] = {0};
    size_t i = 0;

    assert(arr);
    assert(length);

    for (i = 0; length > i; ++i)
    {
        ++histogram[arr[i]];
    }

    pthread_mutex_lock(&g_lock);
    AddResultsToMainHistogram(histogram);
    pthread_mutex_unlock(&g_lock);
}

static void AddResultsToMainHistogram(int *histogram)
{
    size_t i = 0;

    assert(histogram);/* canal */

    for (i = 0; HISTOGRAM_SIZE > i; ++i)
    {
        g_histogram[i] += histogram[i];
    }
}

static void SumHistogramElem(void)
{
    size_t i = 0;

    for (i = 1; HISTOGRAM_SIZE > i; ++i)
    {
        g_histogram[i] += g_histogram[i - 1];
    }
}

static void CopyArr(unsigned char *dest_arr, unsigned char const *src_arr,
                    size_t length)
{
    size_t i = 0;

    assert(dest_arr);/* canal */
    assert(src_arr);/* canal */
    assert(length);/* canal */

    for (i = 0; length > i; ++i)
    {
        dest_arr[i] = src_arr[i];
    }
}
