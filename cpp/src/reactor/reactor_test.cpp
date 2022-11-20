/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Mariana                                     *
 * date: 13.09.22                                        *
 * file: reactor test                                    *
 *********************************************************/
#include <iostream> //cout
#include <fcntl.h>  /// POSIX file control
#include <unistd.h>

#include "../../../system_programming/tcp_udp_pp/udp_pp/udp.h" /* tcp API */

using namespace std;

#include "reactor.hpp"
using namespace ilrd;

#define RUNTEST(test)                     \
    {                                     \
        if (0 == test)                    \
        {                                 \
            cout << "\x1b[0;32m\n";       \
            cout << "OK!\n\n";            \
            cout << "\x1b[0m";            \
        }                                 \
        else                              \
        {                                 \
            cout << "\x1b[1;31m";         \
            cout << "\nTest Failed!\n\n"; \
            cout << "\x1b[0m";            \
        }                                 \
    }
#define TEST(x, y) ValCheck(x, y, __LINE__)
static int ValCheck(double expected_val, double recieved_val, int line);
int Phase1Test();

#define MYPORT (1950)
#define MAXBUFLEN (1024)

enum status
{
    SUCCESS = 0,
    FAILURE
};

struct reactor_with_fd
{
    Reactor *reactor;
    int fd;
};

void WriteCallback2(int port_num, Reactor *reactor)
{
    std::cout << "Second STDOUT callback: " << port_num << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Second STDOUT All Good !! " << std::endl;
    reactor->Remove(STDOUT_FILENO, Operation::WRITE);
}

void WriteCallback(int port_num, Reactor *reactor)
{
    std::cout << "STDOUT callback: " << port_num << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "STDOUT All Good !! " << std::endl;
    reactor->Remove(STDOUT_FILENO, Operation::WRITE);
    std::cout << "Is Remove worked !!" << std::endl;
}

void ReadCallback(int sockfd, struct sockaddr_in *client_addr)
{
    std::cout << "READ callback: " << sockfd << std::endl;
    char buf[MAXBUFLEN];
    UDPRecieveData(sockfd, (char *)buf, MAXBUFLEN, client_addr, 0);
    std::cout << buf << " READ callback end: " << sockfd << std::endl;
    std::cout << "Write turn: " << sockfd << std::endl;
    static const char *message = "unique server message";
    UDPSendData(sockfd, message, strlen(message) + 1, client_addr, 0);
}

int CreateServerUPD(struct sockaddr_in *server_addr)
{
    int sockfd, rv;
    size_t lenaddr = sizeof(struct sockaddr_in);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 > sockfd)
    {
        perror("failed to create socket\n");
        return FAILURE;
    }

    rv = bind(sockfd, (struct sockaddr *)server_addr, lenaddr);
    if (-1 == rv)
    {
        close(sockfd);
        perror("listener: failed to bind\n");
        return FAILURE;
    }

    return sockfd;
}

int main()
{
    cout << "---- Reactor ----\n";

    Phase1Test();

    return 0;
}

int Phase1Test()
{
    int sock_server;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    memset(&client_addr, 0, sizeof(server_addr));
    UDPInitAddr(&server_addr, MYPORT);
    Reactor reactor;

    sock_server = CreateServerUPD(&server_addr);
    reactor.Add(sock_server, std::bind<void>(ReadCallback, sock_server, &client_addr), Operation::READ);
    reactor.Add(STDOUT_FILENO, std::bind<void>(WriteCallback, MYPORT, &reactor), Operation::WRITE);

    reactor.Run();

    return 0;
}