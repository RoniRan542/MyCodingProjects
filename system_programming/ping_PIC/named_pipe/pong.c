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
#include <string.h>   /* strlen */
#include <unistd.h>   /*handling a file descriptor */
#include <errno.h>    /* errno */

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
    char ping_str[10] = "";
    mkfifo(fifo, 0666);

    while (0 < i)
    {
        fd = open(fifo, O_RDONLY);
        if (-1 == fd)
        {
            printf("%d\n", errno);
            return 1;
        }
        read(fd, ping_str, strlen(ping));

        printf("%s\n", ping_str);
        close(fd);
        sleep(1);
        fd = open(fifo, O_WRONLY);
        write(fd, pong, strlen(pong));
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