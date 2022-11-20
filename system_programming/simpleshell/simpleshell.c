/*************************************************
*Name : Ran Aharon Cohen						 *
*Reviewar:	Amir	 	    			         *
*Date: 	08.06.22		            		 	 *
*Description :simple shell	     *
**************************************************/

#include <stdio.h>/* printf, scanf */
#include <stdlib.h>/* system */
#include <sys/types.h>/* pid_t */
#include <sys/wait.h>/* wait */
#include <unistd.h> /* fork, execvp */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */

#include "simpleshell.h"

#define INPUT_SIZE (100)
#define ARGS_NUM (20)

enum status
{
	FAIL = -1,
	SUCCESS = 0,
	EQUAL = 0,
	FAILURE
};

static int SimpleShellFork(void);
static int SimpleShellSystem(void);
static void GetSepArgs(char *input, char **args);

int SimpleShell(const char *fork_or_system)
{
	assert(NULL != fork_or_system);
	
	if(EQUAL == strcmp("fork", fork_or_system))
	{
		return SimpleShellFork();
	}
	else if(EQUAL == strcmp("system", fork_or_system))
	{
		return SimpleShellSystem();
	}
	
	return FAILURE;
}

static int SimpleShellFork(void)
{
	char input[INPUT_SIZE] = "";
	char *args[ARGS_NUM];
	int status = SUCCESS;
	pid_t child_pid;
	
	printf("enter shell command, exit to quit:\n");
	scanf("%[^\n]%*c", input);

	while(EQUAL != strcmp(input,"exit"))
	{
		GetSepArgs(input, args);

		child_pid = fork();
		if(FAIL == child_pid)
		{
			return FAILURE;
		}
		
		if(0 == child_pid)
		{
			execvp(args[0],args);
			exit(FAILURE);
		}
		else
		{
			if(FAIL == waitpid(child_pid, NULL, 1))
			{
				exit(FAILURE);
			}
		}
		scanf("%[^\n]%*c", input);
	}
	
	return status;
}

static int SimpleShellSystem(void)
{
	char input[INPUT_SIZE] = "";
	int status = 0;
	
	scanf("%[^\n]%*c", input);
	
	while(EQUAL != strcmp(input,"exit") && FAIL != status)
	{
		printf("enter shell command, exit to quit:\n");
		scanf("%[^\n]%*c", input);
		
		status = system(input);
	}
	
	return status;
}

static void GetSepArgs(char *input, char **args)
{
	*args = strtok(input," ");
	
	while(*args != NULL)
	{
		++args;
		*args = strtok(NULL," ");
		
	}
}
