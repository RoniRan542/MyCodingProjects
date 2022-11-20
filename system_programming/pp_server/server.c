
#include <stdio.h>    /*for printf*/
#include <sys/time.h> /* for timeval */
#include <unistd.h>   /* close */
#include <string.h>   /*strlen, strcmp */
#include <stdlib.h>   /* for atoi */

#include "../tcp_udp_pp/udp_pp/udp.h" /* udp API */
#include "../tcp_udp_pp/tcp_pp/tcp.h" /* tcp API */
#include "logger.h"                   /* loggeer API */
#include "server.h"                   /* server API */

#define STDIN (0)
#define MAXBUFLEN (50)

enum status
{
    SUCCESS = 0,
    FAILURE
};

static void RemoveFromSet(fd_set *real_set, fd_set *temp_set, int to_remove);
static void AddToSet(fd_set *real_set, fd_set *temp_set, int to_add);
static void InitFdSet(fd_set *set, int udpfd, int tcpfd);

static const char *msg_ping = "ping";
static socklen_t addrlen = sizeof(struct sockaddr);

int StartServer(int udp_port, int tcp_port)
{
    int udpfd, tcpfd, retval, tcp_new_socket;
    int init_max, i, fdmax, status;
    struct sockaddr_in tcp_addr, udp_addr, udp_addr_client, tcp_addr_client;
    char buf[MAXBUFLEN] = "";
    struct timeval tv;
    fd_set readfds, temp;

    UDPInitAddr(&udp_addr, udp_port);
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > udpfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }
    retval = bind(udpfd, (struct sockaddr *)&udp_addr, sizeof udp_addr);
    if (-1 == retval)
    {
        close(udpfd);
        perror("udp server: failed to bind\n");
        return FAILURE;
    }

    TCPInitAddr(&tcp_addr, tcp_port);
    tcpfd = socket(AF_INET, SOCK_STREAM, 0);
    retval = bind(tcpfd, (struct sockaddr *)&tcp_addr, sizeof tcp_addr);
    if (-1 == retval)
    {
        close(tcpfd);
        perror("tcp server: failed to bind...\n");
        return FAILURE;
    }

    retval = listen(tcpfd, 10);
    if (-1 == retval)
    {
        close(tcpfd);
        perror("server: failed to listen...\n");
        return FAILURE;
    }

    InitFdSet(&readfds, udpfd, tcpfd);
    temp = readfds;
    init_max = tcpfd > udpfd ? tcpfd : udpfd;
    fdmax = init_max;

    while (1)
    {
        tv.tv_sec = 7;
        tv.tv_usec = 0;
        status = select(fdmax + 1, &readfds, NULL, NULL, &tv);
        if (-1 == status)
        {
            perror("select()\n");
            return FAILURE;
        }
        else if (0 == status)
        {
            LogWrite("logger.txt", "SERVER: timedout\n");
        }

        if (FD_ISSET(STDIN, &readfds))
        {
            memset(buf, 0, MAXBUFLEN);
            read(STDIN, buf, MAXBUFLEN);
            if (0 == strcmp(buf, "quit\n"))
            {
                return SUCCESS;
            }
            if (0 == strcmp(buf, "ping\n"))
            {
                printf("pong\n");
            }
        }
        else if (FD_ISSET(tcpfd, &readfds))
        {
            tcp_new_socket = accept(tcpfd, (struct sockaddr *)&tcp_addr_client, &addrlen);
            AddToSet(&readfds, &temp, tcp_new_socket);
            fdmax = tcp_new_socket;
        }
        else if (FD_ISSET(udpfd, &readfds))
        {
            memset(&udp_addr_client, 0, addrlen);
            UDPRecieveData(udpfd, buf, MAXBUFLEN, &udp_addr_client, 0);
            printf("udp client: %s\n", buf);
            UDPSendData(udpfd, msg_ping, strlen(msg_ping), &udp_addr_client, 0);
        }
        else
        {
            for (i = init_max; i <= fdmax; i++)
            {
                if (FD_ISSET(i, &readfds))
                {
                    status = TCPRecieveData(i, buf, MAXBUFLEN, MSG_DONTWAIT);
                    if (0 == status)
                    {
                        RemoveFromSet(&readfds, &temp, i);
                        LogWrite("logger.txt", "SERVER: client disconnected\n");
                        break;
                    }
                    printf("tcp client: %s - %d\n", buf, i);
                    TCPSendData(i, msg_ping, MAXBUFLEN, MSG_DONTWAIT);
                }
            }
        }
        readfds = temp;
    }
    close(tcpfd);
    close(udpfd);

    return SUCCESS;
}

int main(int argc, char *argv[])
{
    int p_udc = atoi(argv[1]);
    int p_tcp = atoi(argv[2]);
    (void)argc;
    StartServer(p_udc, p_tcp);

    return SUCCESS;
}

static void RemoveFromSet(fd_set *real_set, fd_set *temp_set, int to_remove)
{
    *real_set = *temp_set;
    FD_CLR(to_remove, real_set);
    *temp_set = *real_set;
}

static void AddToSet(fd_set *real_set, fd_set *temp_set, int to_add)
{
    *real_set = *temp_set;
    FD_SET(to_add, real_set);
    *temp_set = *real_set;
}

static void InitFdSet(fd_set *set, int udpfd, int tcpfd)
{
    FD_ZERO(set);
    FD_SET(udpfd, set);
    FD_SET(tcpfd, set);
    FD_SET(STDIN, set);
}