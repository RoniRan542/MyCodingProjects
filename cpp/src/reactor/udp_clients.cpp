/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Andrei                                        *
 * date: 13.09.22                                        *
 * file: reactor test                              *
 *********************************************************/
#include <iostream> //cout
#include <fcntl.h>  /// POSIX file control
#include <unistd.h>
#include <cstring>
#include <sys/select.h>
#include <chrono>
#include <thread>

#include "../../../system_programming/tcp_udp_pp/udp_pp/udp.h" /* tcp API */

using namespace std;

#define MYPORT (1950)
#define MAXBUFLEN (1024)

enum status
{
    SUCCESS = 0,
    FAILURE
};

static socklen_t addrlen = sizeof(struct sockaddr);

int main()
{
    int result = 0;
    int sock_client[10];
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    size_t lenaddr = sizeof(struct sockaddr_in);
    char buf[MAXBUFLEN] = "";
    static const char *message = "client message";

    UDPInitAddr(&server_addr, MYPORT);
    for (size_t i = 0; i < 10; i++)
    {
        sock_client[i] = socket(AF_INET, SOCK_DGRAM, 0);
        if (0 > sock_client[i])
        {
            perror("failed to create socket\n");
            return FAILURE;
        }
    }

    // std::this_thread::sleep_for(std::chrono::seconds(2));

    std::this_thread::sleep_for(std::chrono::seconds(2));

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << "Client callback: " << sock_client[i] << std::endl;
        UDPSendData(sock_client[i], message, strlen(message) + 1, &server_addr, 0);
        UDPRecieveData(sock_client[i], (char *)buf, MAXBUFLEN, &server_addr, 0);
        std::cout << buf << " Client callback end: " << sock_client[i] << std::endl;
    }

    return 0;
}