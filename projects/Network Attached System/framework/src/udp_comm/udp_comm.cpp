#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "udp_comm.hpp"
#include "handleton.hpp"
#include "nbd_comm.hpp"
namespace ilrd
{

    UdpComm::UdpComm(int capacity, int my_port, int port, int address)
    {
    }

    UdpComm::~UdpComm();
    void UdpComm::SendWrite(const UID &uid, char *buffer, size_t offset, size_t bytes, struct nbd_reply);
    void UdpComm::SendRead(const UID &uid, const char *buffer, size_t offset, size_t bytes, struct nbd_reply);
    void UdpComm::RecvMsg();
    void UdpComm::SendMsg(MessageHeader &msg);
}
