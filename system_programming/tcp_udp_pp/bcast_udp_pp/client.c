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

#define MYPORT (1948)
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
    int rv = 0;
    char buf[MAXBUFLEN] = {0};
    int optval = 1;
    int optlen = sizeof(int);

    UDPInitAddrBroad(&peer_addr, MYPORT);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    rv = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&optval, optlen);
    if (rv > 0)
    {
        close(sockfd);
        perror("Error setting socket to BROADCAST mode\n");
        return FAILURE;
    }

    UDPSendData(sockfd, pong, strlen(pong) + 1, &peer_addr, 0);
    UDPRecieveData(sockfd, (char *)buf, MAXBUFLEN, &peer_addr, 0);
    printf("Server: %s\n", buf);

    close(sockfd);
}

int main()
{
    CreateUPDtalker();

    return SUCCESS;
}