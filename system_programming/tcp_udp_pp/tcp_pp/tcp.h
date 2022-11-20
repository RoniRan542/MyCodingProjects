#ifndef __TCP_H__
#define __TCP_H__

#include <stdio.h>      /*perror*/
#include <sys/socket.h> /*AF_INET*/
#include <arpa/inet.h>  /*sockaddr_in, INADDR_ANY, htons(), htonl()*/
#include <netinet/in.h> /*sockaddr_in, INADDR_ANY, htons()*/

void TCPInitAddr(struct sockaddr_in *addr, size_t port);
int TCPRecieveData(int socketfd, char *buffer, size_t size_buff, int flag);
int TCPSendData(int socketfd, const char *msg, size_t size_msg, int flag);

#endif /*__TCP_H__*/
