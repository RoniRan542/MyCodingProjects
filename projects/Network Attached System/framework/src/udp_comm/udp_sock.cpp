#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <fstream>
#include <iostream>
#include "udp_sock.hpp"

namespace ilrd
{
    UDPsock::UDPsock() : m_fd_sock(socket(PF_INET, SOCK_DGRAM, 0))
    {
        memset(&m_other, 0, sizeof(m_other));
    }

    UDPsock::UDPsock(int my_port, int other_port, int other_ip) : m_fd_sock(socket(AF_INET, SOCK_DGRAM, 0))
    {
        SetIpAndPort(my_port, other_port, other_ip);
    }

    void UDPsock::SetIpAndPort(int my_port, int other_port, int other_ip)
    {
        std::cout << "my port: " << my_port << std::endl;
        std::cout << "other port: " << other_port << std::endl;

        int opt = 1;
        if (setsockopt(m_fd_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.sin_port = htons(my_port);
        hints.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY local ip address
        hints.sin_family = AF_INET;
        getaddrinfo(NULL, my_port, &hints, &res);
        bind(m_fd_sock, res->ai_addr, res->ai_addelen);

        memset(&m_other, 0, sizeof(m_other));
        m_other.sin_port = htons(other_port);
        m_other.sin_addr.s_addr = htonl(other_ip);
        m_other.sin_family = AF_INET;
    }

    void UDPSock::SendMsg(const char *buffer, size_t size_of_buffer)
    {
        m_mutex.lock();
        sendto(m_sd, buffer, size_of_buffer, MSG_NOSIGNAL, (const struct sockaddr *)&m_other, sizeof(m_other));
        m_mutex.unlock();
    }

    void UDPSock::RecvMsg(const char *buffer, size_t size_of_buffer)
    {
        socklen_t sock_len = sizeof(m_other);
        m_mutex_recv.lock();
        long len = recvfrom(m_sd, buffer, size_of_buffer, MSG_NOSIGNAL, (struct sockaddr *)&m_other, &sock_len);
        m_mutex_recv.unlock();
        buffer[len] = '\0';
    }

    int UDPSocket::GetSocket() const
    {
        return (m_fd_sock);
    }

    UDPSock::~UDPSock()
    {
        close(m_fd_sock);
    }

    int UDPSock::GetPeer() const
    {
        int addrlen = sizeof(m_other);
        return getpeername(m_fd_sock, (struct sockaddr *)m_other, &addrlen);
    }
}