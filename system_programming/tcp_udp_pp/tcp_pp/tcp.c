#include <string.h>  /*strlen()*/
#include <strings.h> /* for bzero */

#include "tcp.h"

void TCPInitAddr(struct sockaddr_in *peer_addr, size_t port)
{
    memset(peer_addr, 0, sizeof *peer_addr);

    peer_addr->sin_family = AF_INET;
    peer_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    peer_addr->sin_port = htons(port);
}

int TCPRecieveData(int sockfd, char *buffer, size_t size_buff, int flag)
{
    bzero(buffer, size_buff);
    return recv(sockfd, (void *)buffer, size_buff, flag);
}

int TCPSendData(int sockfd, const char *msg, size_t size_msg, int flag)
{
    return send(sockfd, msg, size_msg, flag);
}
