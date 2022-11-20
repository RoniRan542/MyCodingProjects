
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

#include "../udp_pp/udp.h"

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
    int sockfd = 0;
    struct sockaddr_in peer_addr = {0};
    socklen_t addrlen = sizeof(struct sockaddr);
    int rv = 0;
    int numbytes = 0;
    char buf[MAXBUFLEN] = {0};
    int optval = 1;
    int optlen = sizeof(int);

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

    UDPInitAddrBroad(&peer_addr, MYPORT);

    rv = bind(sockfd, (struct sockaddr *)&peer_addr, sizeof peer_addr);
    if (-1 == rv)
    {
        close(sockfd);
        perror("listener: failed to bind\n");
        return FAILURE;
    }

    UDPRecieveData(sockfd, (char *)buf, MAXBUFLEN, &peer_addr, 0);
    printf("Client: %s\n", buf);
    UDPSendData(sockfd, ping, strlen(ping) + 1, &peer_addr, 0);
    close(sockfd);

    return SUCCESS;
}

int main()
{
    CreateUPDlistener();

    return SUCCESS;
}