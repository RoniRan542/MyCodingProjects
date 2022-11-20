#include <string.h> /*strlen, strcmp */
#include <stdio.h>  /*for printf*/
#include <stdlib.h> /* for atoi */
#include <unistd.h> /* close */
#include <time.h>   /*sleep*/

#include "client.h"                   /*client API*/
#include "../tcp_udp_pp/udp_pp/udp.h" /* udp API */
#include "../tcp_udp_pp/tcp_pp/tcp.h" /* tcp API */
#include "logger.h"                   /* logger API */

#define MAXBUFLEN (50)

enum status
{
    SUCCESS = 0,
    FAILURE
};

static socklen_t addrlen = sizeof(struct sockaddr);
static const char *msg_pong = "pong";

int StartUDP(int port)
{
    int sockfd, i;
    struct sockaddr_in udp_addr;
    char buf[MAXBUFLEN];

    UDPInitAddr(&udp_addr, port);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    for (i = 0; i < 5; ++i)
    {
        UDPSendData(sockfd, msg_pong, strlen(msg_pong) + 1, &udp_addr, MSG_CONFIRM);
        LogWrite("logger.txt", "UDP CLIENT: write ping\n");
        UDPRecieveData(sockfd, (char *)buf, MAXBUFLEN, &udp_addr, MSG_WAITALL);

        printf("Server: %s \n", buf);
        sleep(1);
    }
    close(sockfd);

    return SUCCESS;
}

int StartTCP(int port)
{
    char buf[MAXBUFLEN];
    int sockfd, retval, i;
    struct sockaddr_in tcp_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    TCPInitAddr(&tcp_addr, port);
    retval = connect(sockfd, (struct sockaddr *)&tcp_addr, addrlen);
    if (0 != retval)
    {
        close(sockfd);
        printf("connection with the server failed...\n");
        return FAILURE;
    }

    for (i = 0; i < 5; ++i)
    {
        TCPSendData(sockfd, msg_pong, MAXBUFLEN, 0);
        LogWrite("logger.txt", "TCP CLIENT: write ping\n");
        TCPRecieveData(sockfd, buf, MAXBUFLEN, 0);
        printf("TCPserver: %s\n", buf);
        sleep(1);
    }

    close(sockfd);

    return SUCCESS;
}

int main(int argc, char **argv)
{
    int port = 0;
    (void)argc;
    if (0 == strcmp(argv[1], "tcp"))
    {
        port = atoi(argv[2]);

        return StartTCP(port);
    }
    else if (0 == strcmp(argv[1], "udp"))
    {
        port = atoi(argv[2]);

        return StartUDP(port);
    }

    return SUCCESS;
}
