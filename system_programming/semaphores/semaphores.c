/************************************************
*Name: Ran Aharon Cohen                           *
*Reviewer:                                      *
*Date: 16.06.22                                 *
*File: semaphore.c                                   *
************************************************/
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <assert.h>
#include <stddef.h>

#include "semaphores.h"
#define NUM_SEM_IN_SET (1)
#define SEM_IN_SET (0)

enum status
{
	ERROR = -1,
	SUCCESS = 0,
	FAILURE
};

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

static int SemIncOrDec(semid_t id, int num, int set_undo);
	
semid_t SemCreate(const char *path_name, int proj_id, int sem_value)
{
	key_t key = 0;
	semid_t id = 0; 
	union semun u = {0};
	
	assert(NULL != path_name);
	
	
	key = ftok(path_name, proj_id);
	if(ERROR == key)
	{
		return ERROR;
	}
	id = semget(key, NUM_SEM_IN_SET, 0666 | IPC_CREAT);
	
	if(ERROR == id)
	{
		return ERROR;
	}
	
	u.val = sem_value;
	if(ERROR == semctl(id, SEM_IN_SET, SETVAL, u))
	{
		return ERROR;
	}
	
	return id;
}

int SemDestroy(semid_t id)
{
	if(ERROR == semctl(id, SEM_IN_SET, IPC_RMID))
	{
		return ERROR;
	}
	
	return SUCCESS;
}

int SemIncrement(semid_t id, int num, int set_undo)
{
	return SemIncOrDec(id, num, set_undo);
}

/* to define the undo option set_undo is 1, else 0 */
int SemDecrement(semid_t id, int num, int set_undo)
{
	return SemIncOrDec(id, -num, set_undo);
}

static int SemIncOrDec(semid_t id, int num, int set_undo)
{
	struct sembuf v = { 0, 0, 0}; /* semsignal*/
	v.sem_op = num;
	if(1 == set_undo)
	{
		v.sem_flg = SEM_UNDO;
	}
	
	return semop(id, &v, 1);
}

int SemGetVal(semid_t id)
{
	int val = semctl(id, SEM_IN_SET, GETVAL);

	if(ERROR == val)
	{
		return ERROR;
	}
	
	return val;
}
