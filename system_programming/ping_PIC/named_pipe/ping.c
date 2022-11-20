/**************************************************
 *Name : Ran Aharon Cohen						  *
 *Reviewar:		 	    			              *
 *Date: 	16.08.22		            		  *
 *Description :ping pong PIC semaphore            *
 **************************************************/
#include <stdio.h>    /* for printf */
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>    /*For O_* constants*/
#include <time.h>     /* for sleep */
#include <string.h>   /* for strlen */
#include <unistd.h>   /*handling a file descriptor */

enum status
{
    FAIL = -1,
    SUCCESS = 0,
    EQUAL = 0,
    FAILURE
};
static const char *fifo = "fifo";
static const char *pong = "pong";
static const char *ping = "ping";

int Init()
{
    size_t i = 10;
    int fd = 0;
    char pong_str[10] = "";
    mkfifo(fifo, 0666);

    while (0 < i)
    {
        fd = open(fifo, O_WRONLY);
        write(fd, ping, strlen(ping));
        close(fd);
        fd = open(fifo, O_RDONLY);
        read(fd, pong_str, strlen(pong));
        printf("%s\n", pong_str);
        sleep(1);
        close(fd);
        --i;
    }

    unlink("fifo");
    return 0;
}

int main()
{

    Init();
    return SUCCESS;
}