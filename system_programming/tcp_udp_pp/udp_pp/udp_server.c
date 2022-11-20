/*
** udp_client.c -- a datagram sockets "server" demo
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

static const char *ping = "ping";

int CreateUPDlistener(void)
{
    int sockfd, rv;
    struct sockaddr_in peer_addr;
    size_t lenaddr = sizeof(struct sockaddr_in);
    char buf[MAXBUFLEN] = "";

    UDPInitAddr(&peer_addr, MYPORT);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    rv = bind(sockfd, (struct sockaddr *)&peer_addr, lenaddr);
    if (-1 == rv)
    {
        close(sockfd);
        perror("listener: failed to bind\n");
        return FAILURE;
    }

    while (1)
    {
        UDPSendData(sockfd, ping, strlen(ping) + 1, &peer_addr, 0);
        UDPRecieveData(sockfd, (char *)buf, MAXBUFLEN, &peer_addr, 0);
        printf("Client: %s\n", buf);
    }

    close(sockfd);

    return SUCCESS;
}

int main()
{
    CreateUPDlistener();

    return SUCCESS;
}