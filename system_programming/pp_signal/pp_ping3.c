/*************************************************
*Name : Ran Aharon Cohen						 *
*Reviewar:		 	    			         *
*Date: 	08.06.22		            		 	 *
*Description :ping 3     *
**************************************************/
#define _POSIX_C_SOURCE (199506L)

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

struct sigaction sig = {0};

static int g_child_pid = 0;
void SigHandlerExec(int signal);


void SigInfoHandler(int signal, siginfo_t *info, void *ucontext)
{
	sleep(1);
	
	kill(info->si_pid, SIGUSR2);
}

int main()
{
	sig.sa_sigaction = &SigInfoHandler;
	sig.sa_flags = SA_SIGINFO;
	
	sigaction(SIGUSR1, &sig, NULL);
	
	while(1)
	{
		pause();
		printf("Ping\n");
	}
	
	return 0;
}
