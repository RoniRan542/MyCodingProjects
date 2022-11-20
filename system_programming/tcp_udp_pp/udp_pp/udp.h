#ifndef __UDP_H__
#define __UDP_H__

#include <stdio.h>      /*perror*/
#include <sys/socket.h> /*AF_INET*/
#include <arpa/inet.h>  /*sockaddr_in, INADDR_ANY, htons(), htonl()*/
#include <netinet/in.h> /*sockaddr_in, INADDR_ANY, htons()*/

void UDPInitAddr(struct sockaddr_in *peer_addr, size_t port);
void UDPInitAddrBroad(struct sockaddr_in *peer_addr, size_t port);
void UDPRecieveData(int socketfd, char *buffer, size_t buff_size,
                    struct sockaddr_in *peer_addr, int flag);
void UDPSendData(int socketfd, const char *msg, size_t msg_len,
                 struct sockaddr_in *peer_addr, int flag);

#endif /*__UDP_H__*/
