/*********************************************************************
*Name : Ran Aharon Cohen	 							     		 *
*Reviewar: Schreiber							     				 *
*Date: 28/03/22													   	 *								 
*Description : 	task DS										     	 *
**********************************************************************/

#include <stdlib.h> /* for malloc, free */
#include <unistd.h> /* for sleep */
#include <assert.h>/*for assert*/
#include <time.h>/* sleep */

#include "sched.h"/* header file */
#include "pq_heap.h"/* priority queue(heap) container file */
#include "task.h" /* task structure file */

struct sched
{
	pq_t *pq_sched;
	int quit;
	task_t *curr_task; 
};

enum
{
 RUN,
 STOP
};

static void SleepTime(time_t task_time);
static int RescheduleTask(sched_t *sched, task_t *task, int task_status);
static int IsMatch(const void *task, void *uid);
static int Cmp(const void *new_task, const void * pq_task, void *param);
static int param = 0;

sched_t * SchedCreate(void)
{
	sched_t *sched = (sched_t *)malloc(sizeof(sched_t));
	if(NULL == sched)
	{
		return NULL;
	}
	
	sched->curr_task = NULL;
	sched->pq_sched  = PQCreate(&Cmp, &param);
	if(NULL == sched->pq_sched)
	{
		free(sched);
		sched = NULL;
		return NULL;
	}
	
	return sched;
}

static int Cmp(const void *new_task, const void * pq_task, void *param)
{
	time_t task_time = -1;
	time_t list_item_time = -1;
	
	(void)param;
	assert(new_task);
	assert(pq_task);
	
	task_time = TaskGetTime((task_t *)new_task);
	list_item_time = TaskGetTime((task_t *)pq_task);
	
	return (list_item_time - task_time); 
}
 
void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	SchedClear(sched);
	PQDestroy(sched->pq_sched);
	sched->pq_sched = NULL;
	free(sched);
	sched = NULL;
}

ilrd_uid_t SchedAddTask(sched_t *sched, 
						sc_action_func_t action_func, void *action_param, 							
						sc_clean_up_func_t clean_up_func, void *clean_up_param,
					    time_t time)
{
	task_t *task = NULL;
	assert(NULL != sched);
	assert(NULL != action_func);
	assert(NULL != clean_up_func);
	
	task = TaskCreate(action_func, action_param, clean_up_func,
		 clean_up_param, time);
	
	if(NULL == task)
	{
		return UIDBadUID;	
	}
	
	if(PQEnqueue(sched->pq_sched, task))
	{
		TaskDestroy(task);
		task = NULL;
		return UIDBadUID;	
	}
	
	return TaskGetUID(task);
}

void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid)
{
	void *returned_task = NULL; 
	
	assert(NULL != sched);
	assert(!UIDIsSame(uid,UIDBadUID));
	
	returned_task = PQErase(sched->pq_sched, &uid, &IsMatch);
	if(NULL != returned_task)
	{
		TaskDestroy(returned_task);
	}
}

static int IsMatch(const void *task, void *uid)
{
	assert(NULL != task);
	assert(!UIDIsSame(TaskGetUID((task_t *)task),UIDBadUID));
	
	return (UIDIsSame(TaskGetUID((task_t *)task),*(ilrd_uid_t *)uid));
}

int SchedRun(sched_t *sched)
{
	time_t task_time = -1;
	int sched_stat = 0;
	
	assert(NULL != sched);
	
	sched->quit = RUN;
	
	while(!SchedIsEmpty(sched) &&  RUN == sched->quit)
	{
		sched->curr_task = (task_t *)PQDequeue(sched->pq_sched);
		task_time = TaskGetTime(sched->curr_task);
		
		SleepTime(task_time);
		
		sched_stat += RescheduleTask(sched, sched->curr_task, 
					  								TaskExecute(sched->curr_task));
	}
	
	return sched_stat;
}

static int RescheduleTask(sched_t *sched, task_t *task, int task_status)
{
		int sched_status = 0;
		if(0 == task_status)
		{
			TaskDestroy(task);
		}
		else if(0 > task_status)
		{
			sched_status = 1;
			TaskDestroy(task);
		}
		else
		{
			TaskSetTime(task, task_status);
			if(PQEnqueue(sched->pq_sched, task))
			{
				sched_status = 1;
				TaskDestroy(task);
			}
		}
		
		return sched_status;
}

static void SleepTime(time_t task_time)
{
	
		if(task_time > time(0))
		{
			while(sleep(task_time - time(NULL)))
			{}
		}
}

void SchedStop(sched_t *sched)
{
	assert(NULL != sched);
	sched->quit = STOP;
}

void SchedClear(sched_t *sched)
{
	assert(NULL != sched);
	
	while(!SchedIsEmpty(sched))
	{
		sched->curr_task = PQDequeue(sched->pq_sched);
		TaskDestroy(sched->curr_task);
	}
}

size_t SchedSize(const sched_t *sched)
{
	assert(NULL != sched);
	
	return PQSize(sched->pq_sched);
}

int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	return PQIsEmpty(sched->pq_sched);
}
