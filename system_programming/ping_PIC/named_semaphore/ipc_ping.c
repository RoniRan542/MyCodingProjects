/**************************************************
 *Name : Ran Aharon Cohen						  *
 *Reviewar:		 	    			              *
 *Date: 	16.08.22		            		  *
 *Description :ping pong PIC semaphore            *
 **************************************************/

#include <stdio.h>     /* for printf */
#include <semaphore.h> /* semaphore API */
#include <sys/stat.h>  /* For mode constants */
#include <fcntl.h>     /*For O_* constants*/
#include <time.h>      /* for sleep */

enum status
{
    FAIL = -1,
    SUCCESS = 0,
    EQUAL = 0,
    FAILURE
};

static const char *sem_name1 = "My Semaphora1";
static const char *sem_name2 = "My Semaphora2";

int Init()
{
    size_t i = 10;
    sem_t *sem_pp1 = sem_open(sem_name1, O_CREAT, 0600, 0);
    sem_t *sem_pp2 = sem_open(sem_name2, O_CREAT, 0600, 0);
    if (sem_pp1 == SEM_FAILED || sem_pp2 == SEM_FAILED)
    {
        perror("Init  : [sem_open] Failed\n");
        return 1;
    }

    while (0 < i)
    {

        printf("Ping\n");
        sem_post(sem_pp1);
        sleep(1);
        sem_wait(sem_pp2);

        --i;
    }

    sem_close(sem_pp1);
    sem_close(sem_pp2);
    return 0;
}

int main()
{

    Init();
    return SUCCESS;
}
