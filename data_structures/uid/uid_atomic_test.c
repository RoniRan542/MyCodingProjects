#include <stdio.h>	 /*for printf()*/
#include <pthread.h> /*for thread funcs*/
#include <unistd.h>	 /*sleep*/

#include "../include/uid.h" /*for uid struct*/

enum retrun_status
{
	SUCCESS = 0,
	FAIL
};

void *Test(void *arg);

int main()
{
	pthread_t thr[55] = {0};
	size_t i = 0;
	size_t lut[56] = {0};
	size_t ret_val = 0;

	for (i = 0; i < 55; ++i)
	{
		if (SUCCESS != pthread_create(&thr[i], NULL, &Test, NULL))
		{
			return FAIL;
		}
	}

	for (i = 0; i < 55; ++i)
	{
		pthread_join(thr[i], (void **)&ret_val);
		++lut[(size_t)ret_val];
	}

	for (i = 1; i < 56; ++i)
	{
		if (1 != lut[i])
		{
			printf("FAIL\n");
			return FAIL;
		}
	}

	return SUCCESS;
}

void *Test(void *arg)
{
	ilrd_uid_t my_uid = UIDCreate();

	(void)arg;

	printf("counter = %ld\n", my_uid.counter);

	return (void *)my_uid.counter;
}
