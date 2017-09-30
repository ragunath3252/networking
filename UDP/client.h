#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <iostream>
#include <arpa/inet.h>
#include <string.h>

class udp_client
{
private:
    unsigned int port;
    const int domain = AF_INET;
    const int type = SOCK_DGRAM;
    struct sockaddr_in servaddr;
    int fd;
    char dest[256];

public:
    udp_client(int port, char *src)
    {
        this->port = port;
        strncpy(dest, src, strlen(src));

        servaddr.sin_family = domain;
        inet_aton(dest, &servaddr.sin_addr);
        servaddr.sin_port = htons(port);
    }

    bool start_client()
    {
        std::cout << "Starting UDP client for Destination ip:" << dest << " Port:" << port << std::endl;
        fd = socket(domain, type, 0);
        if (fd < 0)
        {
            std::cout << "socket system call failed\n";
            return false;
        }

        return true;
    }

    void send(char *data, int len)
    {
        int rv = 0;

        if(sendto(fd, data, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            std::cout << "UDP send failed with errno: " << errno << std::endl;
        }
    }

    void stop_client()
    {
        close(fd);
    }

};
