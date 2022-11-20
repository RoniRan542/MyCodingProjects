#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#define ARR_SIZE (100000)
#define PROC_LIM (30653)
#define INPUT (306530000)
enum status
{
	SUCCESS = 0,
	FAILURE
};

static int g_arr[ARR_SIZE] = {0};

static int SumOfDivisors(int num);
void *OperateAssignment(void *val);
static int ForJoin();

int main()
{
	pthread_t IDs[ARR_SIZE] = {0};
	int status = SUCCESS;
	size_t index = 0;
	size_t result = 0;
	time_t start = time(0); 
	pthread_attr_t attr = {0};

	status = pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	for(index = 0; index < PROC_LIM; ++index)
	{	
		if(pthread_create(&IDs[index], &attr, OperateAssignment, (void *)index))
		{
			printf("fail: %ld\n", index);
			while(pthread_create(&IDs[index], &attr, OperateAssignment, (void *)index))
			{
				++index;
			}
			printf("success: %ld\n", index);
		}
	}
	
	printf("100k time: %ld\n", time(0) - start);
	
	/*sleep(10);
	for(index = 0; index < ARR_SIZE; ++index)
	{
		result += ((int)index != g_arr[index]); 
		
		if(0 != result)
		{
			printf("%ld\n", index);
			return FAILURE; 
		}
	}*/
	
	ForJoin();
	
	return status;
}

void *OperateAssignment(void *val)
{
	g_arr[(size_t)val] = (size_t)val;
	
	return NULL;
}

static int ForJoin()
{
	pthread_t IDs[ARR_SIZE] = {0};
	int status = SUCCESS;
	size_t index = 0;
	size_t result = 0;
	time_t start = time(0); 
	pthread_attr_t attr = {0};
	
	
	for(index = 0; index < PROC_LIM; ++index)
	{	
		if(pthread_create(&IDs[index], &attr, OperateAssignment, (void *)index))
		{
			printf("fail: %ld\n", index);
		}
	}
	
	printf("PROC_LIM time: %ld\n", time(0) - start);
	
	for(index = 0; index < PROC_LIM; ++index)
	{
		pthread_join(IDs[index], NULL);
	}
	
	/*sleep(10);*/
	
	for(index = 0; index < PROC_LIM; ++index)
	{
		result += ((int)index != g_arr[index]); 
		
		if(0 != result)
		{
			printf("%ld\n", index);
			return FAILURE; 
		}
	}
	
	return status;
}

