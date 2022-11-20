#include <string.h> /*strlen()*/

#include "udp.h"
static socklen_t addrlen = sizeof(struct sockaddr);

void UDPInitAddr(struct sockaddr_in *addr, size_t port)
{
    memset(addr, 0, sizeof *addr);

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);
}

void UDPInitAddrBroad(struct sockaddr_in *addr, size_t port)
{
    memset(addr, 0, sizeof(struct sockaddr_in));

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = htonl(INADDR_BROADCAST);
    addr->sin_port = htons(port);
}

void UDPRecieveData(int sockfd, char *buffer, size_t buff_size,
                    struct sockaddr_in *peer_addr, int flag)
{
    int bytes_rcved = 0;

    bytes_rcved = recvfrom(sockfd, (char *)buffer, buff_size, flag,
                           (struct sockaddr *)peer_addr, &addrlen);
    buffer[bytes_rcved] = '\0';
}

void UDPSendData(int socketfd, const char *msg, size_t msg_len,
                 struct sockaddr_in *peer_addr, int flag)
{
    sendto(socketfd, msg, msg_len, flag, (const struct sockaddr *)peer_addr,
           addrlen);
}
