/*************************************************
*Name : Ran Aharon Cohen						 *
*Reviewar:		 	    			         *
*Date: 	08.06.22		            		 	 *
*Description :ping pong signal	     *
**************************************************/
#define _POSIX_C_SOURCE 199506L

#include <stdio.h>/* printf, scanf */
#include <stdlib.h>/* system */
#include <sys/types.h>/* pid_t */
#include <sys/wait.h>/* wait */
#include <unistd.h> /* fork, execvp */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */
#include <signal.h>/* signals */
#include "pp_signal.h"



enum status
{
	FAIL = -1,
	SUCCESS = 0,
	EQUAL = 0,
	FAILURE
};

struct sigaction sig = {0};

static int g_child_pid = 0;
static int PingPongFork(void);
void SigHandler(int signal);
static int PingPongForkExec(void);

int PingPong()
{
	return PingPongForkExec();
}

static int PingPongFork(void)
{
	pid_t pid_process = 0;
	sig.sa_handler = &SigHandler;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	
	pid_process = fork();
	if(FAIL == pid_process)
	{
		return FAILURE;
	}
	
	if(0 != pid_process)
	{
		g_child_pid = pid_process;
		kill(g_child_pid, SIGUSR1);
	}
	
	while(1)
	{
		if(0 == pid_process)
		{
			printf("Ping\n");
		}
		else
		{
			printf("Pong\n");
		}
		
		pause();
	}
	
	return 0;
}

static int PingPongForkExec(void)
{
	pid_t pid_process = 0;
	char *args[2] = {NULL, NULL};
	sig.sa_handler = &SigHandler;
	sigaction(SIGUSR2, &sig, NULL);
	
	pid_process = fork();
	if(FAIL == pid_process)
	{
		return FAILURE;
	}
	
	if(0 == pid_process)
	{
		printf("before exec\n");
		printf("%d\n", execvp("./exec", args));
	}
	else
	{
	
		g_child_pid = pid_process;
		sleep(1);
		kill(g_child_pid, SIGUSR1);
		
		while(1)
		{
			pause();
			printf("Pong\n");
		}
	
	}
	
	return 0;
}

void SigHandler(int signal)
{
	if(SIGUSR1 == signal)
	{
		sleep(1);
		kill(getppid(),SIGUSR2);
		
	}
	else if(SIGUSR2 == signal)
	{
		sleep(1);
		kill(g_child_pid, SIGUSR1);
	}
}

int main()
{
	PingPong();
	
	return 0;
}
