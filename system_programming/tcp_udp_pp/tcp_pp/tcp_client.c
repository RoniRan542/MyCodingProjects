#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
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

static const char *pong = "pong";

int CreateTCPtalker(void)
{
    int sockfd, retval;
    struct sockaddr_in peer_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    UDPInitAddr(&peer_addr, MYPORT);
    retval = connect(sockfd, (struct sockaddr *)&peer_addr, sizeof(peer_addr));
    if (0 != retval)
    {
        close(sockfd);
        printf("connection with the server failed...\n");
        return FAILURE;
    }
    TalkTogether(sockfd);
    close(sockfd);

    return SUCCESS;
}

static void TalkTogether(int connfd)
{
    char buff[MAXBUFLEN] = {0};
    int n = 0;
    int i = 0;

    while (10 > i)
    {
        TCPSendData(connfd, pong, strlen(pong) + 1, 0);

        TCPRecieveData(connfd, buff, MAXBUFLEN, 0);
        printf("From client: %s\n", buff);
        ++i;
    }
}

int main()
{
    int server = CreateTCPtalker();
    if (server == FAILURE)
    {
        return FAILURE;
    }

    return SUCCESS;
}