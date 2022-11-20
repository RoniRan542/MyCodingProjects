/*******************************************************************************
 *Name: Adiya Tayri												 			   *
 *Reviewer: Yariv 										 			 		   *
 *Date: 21/08/22												 			   *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_LEN 1024
#define TIMES 5

enum Status
{
    ERROR = -1,
    SUCCESS,
    FAIL
};

typedef struct sockaddr_in sockaddr_in_t;
typedef struct sockaddr sockaddr_t;

static int UDPPPClient(int sockfd, sockaddr_in_t *servaddr, char buffer[]);
static int UDPPPServer(int sockfd, sockaddr_in_t *servaddr, char buffer[]);

static int TCPPPClient(int sockfd, sockaddr_in_t *servaddr, char buffer[]);
static int TCPPPServer(int sockfd, sockaddr_in_t *servaddr, char buffer[]);

int UDPPP(char *input, char *port)
{
    int sockfd = 0;
    char buffer[MAX_LEN];
    sockaddr_in_t servaddr = {0};

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("10.10.1.20");
    servaddr.sin_port = htons(atoi(port));

    if (!strcmp(input, "client"))
    {
        return UDPPPClient(sockfd, &servaddr, buffer);
    }
    else
    {
        return UDPPPServer(sockfd, &servaddr, buffer);
    }
}

static int UDPPPClient(int sockfd, sockaddr_in_t *servaddr, char buffer[])
{
    int n = 0;
    int i = 0;
    unsigned int len = sizeof(sockaddr_in_t);

    for (; TIMES > i; ++i)
    {
        if (ERROR == sendto(sockfd, "Ping", strlen("Ping") + 1, MSG_CONFIRM,
                            (const sockaddr_t *)servaddr, sizeof(*servaddr)))
        {
            puts("client failed sendto");
            close(sockfd);

            return FAIL;
        }

        if (ERROR == (n = recvfrom(sockfd, buffer, MAX_LEN, MSG_WAITALL,
                                   (sockaddr_t *)servaddr, &len)))
        {
            puts("client failed recvfrom");
            close(sockfd);

            return FAIL;
        }

        buffer[n] = '\0';
        printf("UDP Server : %s\n", buffer);
        memset(buffer, 0, MAX_LEN);
        sleep(1);
    }
    close(sockfd);

    return SUCCESS;
}

static int UDPPPServer(int sockfd, sockaddr_in_t *servaddr, char buffer[])
{
    int n = 0;
    int i = 0;
    unsigned int len = sizeof(sockaddr_in_t);
    sockaddr_in_t cliaddr = {0};

    if (bind(sockfd, (const sockaddr_t *)servaddr, sizeof(*servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    memset(&cliaddr, 0, len);
    for (; TIMES > i; ++i)
    {
        if (ERROR == (n = recvfrom(sockfd, buffer, MAX_LEN, MSG_WAITALL,
                                   (sockaddr_t *)&cliaddr, &len)))
        {
            puts("server failed recvfrom");

            return FAIL;
        }

        buffer[n] = '\0';
        printf("UDP Client : %s\n", buffer);
        sleep(1);

        memset(buffer, 0, MAX_LEN);

        if (ERROR == sendto(sockfd, "Pong", strlen("Pong") + 1, MSG_CONFIRM,
                            (const sockaddr_t *)&cliaddr, len))
        {
            puts("server failed sendto");

            return FAIL;
        }
    }

    return SUCCESS;
}

int TCPPP(char *input, char *port)
{
    int sockfd;
    sockaddr_in_t servaddr;
    char buffer[MAX_LEN];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(sockaddr_in_t));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(port));

    if (!strcmp(input, "client"))
    {
        servaddr.sin_addr.s_addr = inet_addr("10.10.1.20");

        return TCPPPClient(sockfd, &servaddr, buffer);
    }
    else
    {
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

        return TCPPPServer(sockfd, &servaddr, buffer);
    }
}

static int TCPPPClient(int sockfd, sockaddr_in_t *servaddr, char buffer[])
{
    unsigned int len = sizeof(sockaddr_in_t);
    int i = 0;
    int n;

    if (connect(sockfd, (sockaddr_t *)servaddr, len))
    {
        printf("connection with the server failed...\n");
        exit(1);
    }

    for (; TIMES > i; ++i)
    {
        if (ERROR == send(sockfd, "Ping", strlen("Ping") + 1, 0))
        {
            puts("client failed sendto");
            close(sockfd);

            return FAIL;
        }

        if (ERROR == (n = recv(sockfd, buffer, MAX_LEN, 0)))
        {
            puts("client failed recvfrom");
            close(sockfd);

            return FAIL;
        }

        buffer[n] = '\0';
        printf("TCP Server : %s\n", buffer);
        memset(buffer, 0, MAX_LEN);
        sleep(1);
    }

    close(sockfd);

    return SUCCESS;
}

static int TCPPPServer(int sockfd, sockaddr_in_t *servaddr, char buffer[])
{
    unsigned int len = sizeof(sockaddr_in_t);
    int i = 0;
    int connfd;
    int n = 0;
    sockaddr_in_t cliaddr = {0};

    if ((bind(sockfd, (sockaddr_t *)servaddr, sizeof(sockaddr_in_t))))
    {
        printf("socket bind failed...\n");
        exit(1);
    }
    memset(&cliaddr, 0, len);

    if ((listen(sockfd, 1)) < 0)
    {
        printf("Listen failed...\n");
        exit(1);
    }

    connfd = accept(sockfd, (sockaddr_t *)&cliaddr, &len);
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(1);
    }

    for (; TIMES > i; ++i)
    {
        if (ERROR == (n = recv(connfd, buffer, MAX_LEN, 0)))
        {
            puts("server failed recvfrom");

            return FAIL;
        }

        buffer[n] = '\0';
        printf("TCP Client : %s\n", buffer);
        sleep(1);

        memset(buffer, 0, MAX_LEN);

        if (ERROR == send(connfd, "Pong", strlen("Pong") + 1, 0))
        {
            puts("server failed sendto");

            return FAIL;
        }
    }

    return SUCCESS;
}

int UDPBroadcast(char *input, char *port)
{
    int enabled = 1;
    int sockfd = 0;
    char buffer[MAX_LEN];
    sockaddr_in_t servaddr = {0};

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_BROADCAST;
    servaddr.sin_port = htons(atoi(port));

    if (!strcmp(input, "client"))
    {
        setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &enabled, sizeof(enabled));

        if (ERROR == setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &enabled,
                                sizeof(enabled)))
        {
            perror("setsockopt failed\n");
            close(sockfd);
            exit(1);
        }

        return UDPPPClient(sockfd, &servaddr, buffer);
    }
    else
    {
        return UDPPPServer(sockfd, &servaddr, buffer);
    }
}