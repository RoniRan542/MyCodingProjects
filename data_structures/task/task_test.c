/*********************************************************************
*Name : Ran Aharon Cohen	 							     		 *
*Reviewar: 🐕️  🤯️										             *
*Date:  03/22/22													 *												 
*Description : 	task 										     	 *
**********************************************************************/
#include <stdio.h> /* for printf */

#include "task.h" /* sorted list header*/

#define RUNTEST(test) {\
            if (0 == test)\
            {\
                printf("\x1b[0;32m");\
                printf("OK!\n\n");\
                printf("\x1b[0m");\
            }\
            else\
            {\
                printf("\x1b[1;31m");\
                printf("\nTest Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }


int TestCreateDestroy(void);
int TestExecute(void);
int TestGetSetTime(void);

int ActionFunc(void *param);
void CleanUpFunc(void *param);


int main()
{
	printf("------------------------------------------\n");
	printf("-------- TEST Create and Destroy --------\n");
	RUNTEST(TestCreateDestroy());
	printf("------------------------------------------\n");
	printf("-------- TEST Execute----------------\n");
	RUNTEST(TestExecute());
	printf("------------------------------------------\n");
	printf("-------- TEST Get Set Time --------\n");
	RUNTEST(TestGetSetTime());
	
	return 0;
}

int TestCreateDestroy(void)
{
    int result = 0;
    int a = 63;
    int b = 37;
    time_t my_time = 0;
    task_t *task = NULL;
	
	
	my_time = time(NULL);
	task = TaskCreate(&ActionFunc, &a, &CleanUpFunc, &b, my_time);
	
	result += (NULL == task);
	TaskDestroy(task);
	result += (36 != b);
	return result;
}

int TestExecute(void)
{
    int result = 0;
    int a = 37;
    int b = 63;
    time_t my_time = 0;
    task_t *task = NULL;
	
	my_time = time(NULL);
	task = TaskCreate(&ActionFunc, &a, &CleanUpFunc, &b, my_time);
	
	result += (TaskExecute(task) != 0);
	result += (38 != a);
	TaskDestroy(task);
	
	return result;
}

int TestGetSetTime(void)
{
    int result = 0;
    int a = 55;
    int b = 44;
    time_t my_time = 0;
    time_t next_time = 0;
    task_t *task = NULL;
	my_time = time(NULL);
	task = TaskCreate(&ActionFunc, &a, &CleanUpFunc, &b, my_time);
	result += (TaskGetTime(task) != my_time);
	next_time = TaskGetTime(task);
	TaskSetTime(task, 1);
	result += (TaskGetTime(task) != (next_time + 1));
	
	TaskDestroy(task);
	
	return result;
}

int ActionFunc(void *param)
{
	++*(int *)param;
	
	return 0;
}

void CleanUpFunc(void *param)
{
	--*(int *)param;
}

