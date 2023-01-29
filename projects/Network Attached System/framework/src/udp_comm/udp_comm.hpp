/* -------------------------------------------------------------------------- *
 * FILENAME      -    distributer.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    27/11/22
 * -------------------------------------------------------------------------- */

#ifndef __UDP_COMM_HPP__
#define __UDP_COMM_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>

#include "message.hpp"
#include "udp_sock.hpp"
#include "uid.hpp"

namespace ilrd
{
    class UdpComm
    {
    public:
        UdpComm(int capacity, int my_port, int port, int address);
        ~UdpComm();
        void SendWrite(const UID &uid, char *buffer, size_t offset, size_t bytes, struct nbd_reply);
        void SendRead(const UID &uid, const char *buffer, size_t offset, size_t bytes, struct nbd_reply);
        void RecvMsg();

    private:
        void SendMsg(MessageHeader &msg);
        int m_capacity;
        UDPSock m_socket;
    };

}

#endif // __UDP_COMM_HPP__