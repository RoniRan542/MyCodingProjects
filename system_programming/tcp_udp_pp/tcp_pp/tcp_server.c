#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#include "tcp.h"

#define MYPORT (8000)
#define MAXBUFLEN (100)

enum status
{
    SUCCESS = 0,
    FAILURE
};

static void TalkTogether(int connfd);

static const char *ping = "ping";

int CreateTCPlistener(void)
{
    int sockfd = 0, connfd = 0, retval = 0;
    struct sockaddr_in peer_addr = {0};
    socklen_t addrlen = sizeof(struct sockaddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    TCPInitAddr(&peer_addr, MYPORT);
    retval = bind(sockfd, (struct sockaddr *)&peer_addr, sizeof peer_addr);
    if (-1 == retval)
    {
        close(sockfd);
        perror("server: failed to bind...\n");
        return FAILURE;
    }

    retval = listen(sockfd, 10);
    if (-1 == retval)
    {
        close(sockfd);
        perror("server: failed to bind...\n");
        return FAILURE;
    }

    connfd = accept(sockfd, (struct sockaddr *)&peer_addr, &addrlen);
    if (0 > connfd)
    {
        close(sockfd);
        perror("failed to create conn socket\n");
        return FAILURE;
    }

    TalkTogether(connfd);
    close(sockfd);

    return SUCCESS;
}

static void TalkTogether(int connfd)
{
    char buff[MAXBUFLEN] = {0};
    int i = 0;

    while (10 > i)
    {

        TCPRecieveData(connfd, buff, MAXBUFLEN, 0);
        printf("From Server: %s\t To client :\n", buff);

        TCPSendData(connfd, ping, strlen(ping) + 1, 0);
        ++i;
    }
}

int main()
{
    int server = CreateTCPlistener();
    if (server == FAILURE)
    {
        return FAILURE;
    }

    return SUCCESS;
}