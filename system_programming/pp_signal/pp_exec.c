/*************************************************
*Name : Ran Aharon Cohen						 *
*Reviewar:		 	    			         *
*Date: 	08.06.22		            		 	 *
*Description :ping pong exec	     *
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



enum status
{
	FAIL = -1,
	SUCCESS = 0,
	EQUAL = 0,
	FAILURE
};

struct sigaction sig1 = {0};

static int g_child_pid = 0;
void SigHandlerExec(int signal);

void SigHandlerExec(int signal)
{
	sleep(1);
	kill(getppid(),SIGUSR2);
}

int main()
{
	
	sig1.sa_handler = &SigHandlerExec;
	sigaction(SIGUSR1, &sig1, NULL);
	
	while(1)
	{
		
		pause();
		printf("Ping\n");
	}
	
	return 0;
}
