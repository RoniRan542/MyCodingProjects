/*
** listener.c -- a datagram sockets "server" demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#include "udp.h"

#define MYPORT (1950)
#define MAXBUFLEN (100)

enum status
{
    SUCCESS = 0,
    FAILURE
};

static const char *pong = "pong";

int CreateUPDtalker(void)
{
    int sockfd = 0;
    struct sockaddr_in peer_addr = {0};
    char buf[MAXBUFLEN] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    peer_addr.sin_family = AF_INET;
    peer_addr.sin_addr.s_addr = INADDR_ANY;
    peer_addr.sin_port = htons(MYPORT);

    UDPSendData(sockfd, pong, strlen(pong) + 1,
                &peer_addr, 0);
    UDPRecieveData(sockfd, (char *)buf, MAXBUFLEN,
                   &peer_addr, 0);
    printf("Server: %s\n", buf);

    close(sockfd);

    return SUCCESS;
}

int main()
{
    CreateUPDtalker();

    return SUCCESS;
}