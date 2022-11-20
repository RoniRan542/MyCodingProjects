/************************************************
*Name: Ran Aharon Cohen                           *
*Reviewer:                                      *
*Date: 14.06.22                                 *
*File: 100k_threads_test.c                              *
************************************************/
#include <stdio.h> /* printf */
#include <sys/time.h> /* ulimit */
#include <sys/resource.h> /* ulimit */
#include <time.h> /* time */
#include <pthread.h> /* thread */
#include <omp.h>/* for openMP */

#define PROC_LIM (30653)
#define INPUT (3065300000)
#define RANGE (100000)
#define RANGE2 (766325000)
#define RANGE3 (218950000)
#define LIBS_NUM 8

enum status
{
    SUCCESS = 0,
    FAILURE
};

int Ex4();
int Ex5();
void *SumDivs(void *arr);
size_t GetMaxThreads();
static unsigned long SumOfDivsLoop(unsigned long  num);

int main()
{
    int status = 0;
    
    /*Ex4();*/
    status = Ex5();

    return status;
}

int Ex4()
{
    int status = 0; 
    size_t sum = 0;/* num we check divisors is 3065300000 */
    size_t retval = 0;
    size_t i = 0;
    pthread_t tid[PROC_LIM];
    time_t t0 = time(NULL);
	time_t t1 = 0;
    for (i = 0; i < LIBS_NUM; ++i)
    {
        status = pthread_create(&tid[i], NULL, &SumDivs, (void *)i);

    }

    for (i = 0; i < LIBS_NUM; ++i)
    {
        status += pthread_join(tid[i], (void **)&retval);
		if(0 != status)
		{
			return FAILURE;
		}
        sum += retval;
    } 
	
    printf("\ntime elapsed: %ld\n", time(NULL) - t0);
	
    return status;
}

int Ex5()
{
    int status = 0; /* num we check divisors is 3093200000 */
    
    time_t t0 = time(NULL);
    #pragma omp parallel
	{
		SumOfDivsLoop(INPUT);
    }
    printf("\ntime elapsed loop: %ld\n", time(NULL) - t0);
	
    return status;
}

void *SumDivs(void *thread_num)
{
    size_t start = (RANGE3 * (size_t)thread_num) + 1;
    size_t end = (RANGE3 * ((size_t)thread_num + 1)) + 1;
    size_t range_sum = 0;

    for (; start < end; ++start)
    {
        if (0 == INPUT % start)
        {
            range_sum += start;
        }
    }

    return (void *)range_sum;
}

size_t GetMaxThreads()
{
    struct rlimit rlim;

    if (0 != getrlimit(RLIMIT_NPROC, &rlim))
    {
        return FAILURE;
    }

    return rlim.rlim_max - 1;
}

static unsigned long SumOfDivsLoop(unsigned long num)
{
    unsigned long sum_of_divisors = 0;
    unsigned long i = 0;
	
    for(i = 1 ; i < num ; ++i)
    {
        if(0 == num % 1)
        {
            sum_of_divisors += i;
        }
    }
	
    return sum_of_divisors;
}
