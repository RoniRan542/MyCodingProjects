#ifndef __UDP_SOCK_HPP__
#define __UDP_SOCK_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <string>
#include <arpa/inet.h> /* sockadrr_in */
#include <mutex>
namespace ilrd
{
    class UDPsock
    {
    public:
        UDPSock();
        UDPSock(int my_port, int other_port, int other_ip);
        void SetIpAndPort(int my_port, int other_port, int other_ip);
        void SendMsg(const char *buffer, size_t size_of_buffer);
        int GetPeer() const;
        void RecvMsg(char *buffer, size_t size_of_buffer);
        int GetSocket() const;

    private:
        int m_fd_sock;
        struct sockaddr_in m_other;
        std::mutex m_mutex;
        std::mutex m_mutex_recv;
    };
}

#endif //__UDP_SOCK_HPP__