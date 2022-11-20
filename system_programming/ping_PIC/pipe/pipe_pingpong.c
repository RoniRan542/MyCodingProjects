
/**************************************************
 *Name : Ran Aharon Cohen						  *
 *Reviewar:		 	    			              *
 *Date: 	16.08.22		            		  *
 *Description :ping pong PIC Pipe            *
 **************************************************/
#include <unistd.h>    /*pid_t, fork, execvp*/
#include <sys/types.h> /*pid_t, fork, execvp*/
#include <stdio.h>     /* for printf */
#include <unistd.h>    /*handling a file descriptor */
#include <time.h>      /* for sleep */
#include <string.h>    /* strlen */

enum status
{
    FAIL = -1,
    SUCCESS = 0,
    EQUAL = 0,
    FAILURE = 1
};

int Init()
{
    size_t i = 10;
    size_t j = 10;
    pid_t pid = 0;
    char child_str[10] = "";
    char parent_str[10] = "";
    char *ping = "ping";
    char *pong = "pong";
    int pipe_ping[2];
    int pipe_pong[2];
    int read_pong;
    int write_ping;
    int read_ping;
    int write_pong;

    if (pipe(pipe_ping) == -1)
    {
        printf("Pipe Failed\n");
        return 1;
    }
    read_ping = pipe_ping[0];
    write_ping = pipe_ping[1];

    if (pipe(pipe_pong) == -1)
    {
        printf("Pipe Failed\n");
        return 1;
    }
    read_pong = pipe_pong[0];
    write_pong = pipe_pong[1];

    pid = fork();
    if (pid == -1)
    {
        return FAILURE;
    }
    else if (pid == (pid_t)0)
    {
        close(read_pong);
        close(write_ping);
        while (0 < i)
        {
            read(read_ping, parent_str, strlen(ping));
            printf("%s\n", parent_str);
            write(write_pong, pong, strlen(pong));
            --i;
        }
    }
    else
    {
        close(read_ping);
        close(write_pong);
        while (0 < j)
        {
            write(write_ping, ping, strlen(ping));
            read(read_pong, child_str, strlen(pong));
            printf("%s\n", child_str);
            --j;
        }
    }

    return 0;
}

int main()
{

    Init();
    return SUCCESS;
}