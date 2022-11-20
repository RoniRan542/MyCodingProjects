/*********************************************************************
*Name : Ran Aharon Cohen	 							     		 *
*Reviewar: 🐕️  🤯️								     *
*Date: 28/03/22													 *												 
*Description : 	task DS										     	 *
********************************************************************************/
#include <stdlib.h>/* malloc, free*/
#include <assert.h>/* assert*/

#include "task.h"
#include "uid.h"

enum{
	SUCCESS,
	FAILURE
};

struct task
{
    time_t time;
    action_func_time_t action_func;
    void *action_param;
    clean_up_func_t clean_up_func;
    void *clean_up_param;
    ilrd_uid_t uid;
};



static int Init(task_t *task, action_func_time_t action_func, void *action_param, 
clean_up_func_t clean_up_func, void *clean_up_param, time_t time);

task_t *TaskCreate(action_func_time_t action_func, void *action_param, 
clean_up_func_t clean_up_func, void *clean_up_param, time_t time)
{
	int status = 0;
	task_t *task = NULL;
	assert(NULL != action_func);
	assert(NULL != clean_up_func);
	assert(-1 != time);

	task = (task_t *)malloc(sizeof(task_t));
	if(NULL == task)
	{
		return NULL;
	}
	
	status = Init(task, action_func, action_param, clean_up_func, clean_up_param, time);
	if(SUCCESS != status)
	{
		free(task);
		task = NULL;
		return NULL;
	}
	
	return task;
}

static int Init(task_t *task, action_func_time_t action_func, void *action_param, 
clean_up_func_t clean_up_func, void *clean_up_param, time_t time)
{
	assert(NULL != task);
	assert(NULL != action_func);
	assert(NULL != clean_up_func);
	assert(-1 != time);
	
	task->action_func = action_func;
	task->action_param = action_param;
	task->clean_up_func = clean_up_func;
	task->clean_up_param = clean_up_param;
	task->time = time;
	task->uid = UIDCreate();
	if(UIDIsSame(UIDBadUID, task->uid))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	task->clean_up_func(task->clean_up_param);
	free(task);
	task = NULL;
}

int TaskExecute(task_t *task)
{
	assert(NULL != task);
	
	return task->action_func(task->action_param);
}

time_t TaskGetTime(const task_t *task)
{
	assert(NULL != task);
	
	return task->time;
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}

void TaskSetTime(task_t *task, time_t add_time)
{
	assert(NULL != task);
	
	task->time += add_time;
}
