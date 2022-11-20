#include <stdio.h> /* printf */ 
#include <time.h>/*time*/
#include <string.h>/*strlen*/

#include "sched.h"

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
                printf("Test Failed!\n\n");\
                printf("\x1b[0m");\
            }\
        }

int TestInt(int expected, int result);
int TestCreate(void);
int TestAddRemove(void);
int TestRun(void);
int TestStop(void);
static int ActionFunc(void *param);
static void CleanUpFunc(void *param);
static void CleanUpFunc2(void *param);
static int RemoveFunc(void *param);
static int ActionStop(void *param);
static int ActionFileStop(void *param);
void PrintUid(ilrd_uid_t uid);


int main()
{
    int result = 0;
    printf("\n\n***************************************************************\n");
    printf("*              Test For Create Function                       *\n");
    printf("***************************************************************\n\n");
    result = TestCreate();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
    printf("\n\n***************************************************************\n");
    printf("*              Test For Add and Remove                  *\n");
    printf("***************************************************************\n\n");
    result = TestAddRemove();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	printf("\n\n***************************************************************\n");
    printf("*              Test For Run                 *\n");
    printf("***************************************************************\n\n");
    result = TestRun();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
   	
printf("\n\n***************************************************************\n");
    printf("*              Test For Stop                 *\n");
    printf("***************************************************************\n\n");
    result = TestStop();
   	printf("THE FINAL RESULT OF THE TEST: ");
   	RUNTEST(result);
    return 0;
}

int TestCreate(void)
{
	int result = 0;
	sched_t *sched = SchedCreate();
	printf("Check if the new sched is empty:\n");
	result += TestInt(1, SchedIsEmpty(sched));
	RUNTEST(result);
	printf("Check the new sched has size 0:\n");
	result += TestInt(0, SchedSize(sched));
	RUNTEST(result);
	SchedDestroy(sched);
	
	return result;
}

int TestAddRemove(void)
{
	int result = 0;
	time_t my_time1 = -1;
	time_t my_time2 = -1;
	time_t my_time3 = -1;
	ilrd_uid_t uid1;
	ilrd_uid_t uid2;
	ilrd_uid_t uid3; 
	sched_t *sched = SchedCreate();
	my_time1 = time(0);	
	printf("Check if the new sched is empty:\n");
	result += TestInt(1, SchedIsEmpty(sched));
	RUNTEST(result);
	printf("Check the new sched has size 0:\n");
	result += TestInt(0, SchedSize(sched));
	RUNTEST(result);
	uid1 = SchedAddTask(sched, &ActionFunc, 
						NULL, &CleanUpFunc,
 						NULL, my_time1);
 	printf("Check if the new sched is empty:\n");
	result += TestInt(0, SchedIsEmpty(sched));
	RUNTEST(result);
	printf("Check the new sched has size 1:\n");
	result += TestInt(1, SchedSize(sched));
	RUNTEST(result);
	printf("Check the new sched has size 2:\n");
	result += TestInt(0, UIDIsSame(uid1,UIDBadUID));
	RUNTEST(result);
	PrintUid(uid1);
	my_time2 = time(0);	
	uid2 = SchedAddTask(sched, &ActionFunc, 
						NULL, &CleanUpFunc,
 						NULL, my_time2);
 	printf("Check the new sched has size 2:\n");
	
	result += TestInt(2, SchedSize(sched));
	RUNTEST(result);
	my_time3 = time(0);	
	uid3 = SchedAddTask(sched, &ActionFunc, 
						NULL, &CleanUpFunc,
 						NULL, my_time3);
 	printf("Check the new sched has size 3:\n");
	result += TestInt(3, SchedSize(sched));
	RUNTEST(result);
	SchedRemoveTask(sched, uid1);
	
	printf("Check the remove sched has size 2:\n");
	result += TestInt(2, SchedSize(sched));
	RUNTEST(result);
	SchedClear(sched);
	printf("Check the remove sched has size 0:\n");
	result += TestInt(0, SchedSize(sched));
	RUNTEST(result);
	SchedDestroy(sched);
	
	return result;
}

int TestRun(void)
{
	int result = 0;
	time_t my_time = -1;
	
	ilrd_uid_t uid1;
	ilrd_uid_t uid2;
	ilrd_uid_t uid3; 
	sched_t *sched = SchedCreate();
	printf("Check if the new sched is empty:\n");
	result += TestInt(1, SchedIsEmpty(sched));
	RUNTEST(result);
	printf("Check the new sched has size 0:\n");
	result += TestInt(0, SchedSize(sched));
	RUNTEST(result);
	uid1 = SchedAddTask(sched, &ActionFunc, 
						NULL, &CleanUpFunc,
 						NULL, (time(NULL)+2));
 	printf("Check if the new sched is empty:\n");
	result += TestInt(0, SchedIsEmpty(sched));
	RUNTEST(result);
	printf("Check the new sched has size 1:\n");
	result += TestInt(1, SchedSize(sched));
	RUNTEST(result);
	printf("Check the new sched has size 2:\n");
	result += TestInt(0, UIDIsSame(uid1,UIDBadUID));
	RUNTEST(result);
	uid2 = SchedAddTask(sched, &ActionFunc, 
						NULL, &CleanUpFunc,
 						NULL,  (time(NULL)+4));
 	uid3 = SchedAddTask(sched, &ActionFunc, 
						NULL, &CleanUpFunc,
 						NULL,  (time(NULL)+6));
	/*SchedRun(sched);*/
	SchedDestroy(sched);
	
	return result;
}

typedef struct sched_and_uid
{
	sched_t *sched;
	ilrd_uid_t uid;
} my_struct;

int TestStop(void)
{
	
	int result = 0;
	time_t tm = -1;
	int count1 = 1;
	int count2 = 2;
	int count3 = 3;
	int count4 = 4;
	int count5 = 0;
	
	ilrd_uid_t uid1;
	ilrd_uid_t uid2;
	ilrd_uid_t uid3; 
	ilrd_uid_t uid4; 
	
	my_struct sched_uid_struct = {NULL,{0,0,0}};
	sched_t *sched = SchedCreate();
	
	tm = time(0);
	printf("Check if the new sched is empty:\n");
	result += TestInt(1, SchedIsEmpty(sched));
	RUNTEST(result);
	printf("Check the new sched has size 0:\n");
	result += TestInt(0, SchedSize(sched));
	RUNTEST(result);
	uid1 = SchedAddTask(sched, &ActionFunc, NULL, &CleanUpFunc2, &count1,(tm+2));
	SchedAddTask(sched, &ActionFileStop, sched, &CleanUpFunc2, &count5,(tm+3));
	uid2 = SchedAddTask(sched, &ActionFunc, NULL, &CleanUpFunc2, &count2,(tm+5));
	/*SchedAddTask(sched, &ActionStop, sched, &CleanUpFunc2, &count5,(tm+5));*/
 	uid3 = SchedAddTask(sched, &ActionFunc, NULL, &CleanUpFunc2, &count3,(tm+7));
 	uid4 = SchedAddTask(sched, &ActionFunc, NULL, &CleanUpFunc2, &count4,(tm+8));
 	sched_uid_struct.uid = uid2;
 	sched_uid_struct.sched = sched;
 	/*uid4 = SchedAddTask(sched,&RemoveFunc,&sched_uid_struct, &CleanUpFunc2,&count4,(tm));*/
 	
	SchedRun(sched);
	SchedDestroy(sched);
	
	return result;
}

static int ActionFunc(void *param)
{
	(void)param;
	
	printf("ActionFunc success\n\n");
	
	return 0;
}

static int ActionStop(void *param)
{
	printf("Action stop function\n\n");
	SchedStop(param);
	
	return 0;
}

static int ActionFileStop(void *param)
{
	int i = 0;
    int len = 0;
    char input[18] = "\0";
    FILE *file = NULL;
    
	printf("Action open file \n\n");
	
	file = fopen("stop_sched_file.txt", "a+");
    if (NULL == file)
    {
        printf("fopen 'a' failed.\n");
        return -1;
    }
	fclose(file);
	
	file = fopen("stop_sched_file.txt", "r");
    if (NULL == file)
    {
        printf("fopen r failed.\n");
        return -1;
    }

    fgets(input,5,file);
	len = strlen(input);
    for (i = 0; i < len; ++i)
    {
        input[i] = tolower(input[i]);
    }
    printf("%s\n",input);
	if(0 != strcmp(input, "stop"))
	{
		printf("rescheduling to 3 seconds from now\n");
        fclose(file);
		return 3;/*reschduling*/
	}
	else
	{
		printf("stoping scheduler!\n");
        fclose(file);
		SchedStop(param);
		remove("stop_sched_file.txt");
		return 0;
	}
}

static int RemoveFunc(void *param)
{
	my_struct *sched_uid_struct = (my_struct *)param;
	(void)param;
	
	SchedRemoveTask(sched_uid_struct->sched, sched_uid_struct->uid);
	printf("ActionFunc success\n\n");
	return 0;
}

static void CleanUpFunc(void *param)
{
	(void)param;
	printf("CleanUpFunc success\n\n");
}

static void CleanUpFunc2(void *param)
{
	printf("CleanUpFunc success %d\n\n",*(int *)param);
}

int TestInt(int expected, int result)
{
	return ((expected == result) ? 0 : 1);
}

void PrintUid(ilrd_uid_t uid)
{
    printf("pid: %d\n", uid.pid);
    printf("time: %ld\n", uid.time);
    printf("counter: %lu\n", uid.counter);
    printf("\n\n");
}


