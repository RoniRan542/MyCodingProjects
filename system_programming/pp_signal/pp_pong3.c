/*************************************************
*Name : Ran Aharon Cohen						 *
*Reviewar:		 	    			         *
*Date: 	08.06.22		            		 	 *
*Description :ping pong3      *
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



static pid_t ex_pid = 0;
enum status
{
	FAIL = -1,
	SUCCESS = 0,
	EQUAL = 0,
	FAILURE
};

struct sigaction sig = {0};

void SigHandler(int signal);


void SigHandler(int signal)
{
	sleep(1);
	kill(ex_pid, SIGUSR1);
}

int main(int argc, char *argv[])
{
	
	sig.sa_handler = &SigHandler;
	sigaction(SIGUSR2, &sig, NULL);
	ex_pid = atoi(argv[1]);
	
	kill(ex_pid, SIGUSR1);
	while(1)
	{	
		pause();
		printf("pong\n");
	}
	
	return 0;
}
