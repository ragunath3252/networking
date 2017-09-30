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
    struct sockaddr_in myaddr;
    int fd;
    char dest[256];

public:
    udp_client(int port, char *src)
    {
        this->port = port;

        strncpy(dest, src, strlen(src));
        std::cout << "Destination is " << dest << std::endl;

        myaddr.sin_family = AF_INET;
        inet_aton(dest, &myaddr.sin_addr);
        myaddr.sin_port = htons(port);
    } bool start_client()
    {
        int rv;

        std::cout << "starting client";
        fd = socket(domain, type, 0);
        std::cout.flush();

        if (fd < 0)
        {
            std::cout << "socket system call failed\n";
            return false;
        }
        else
            std::cout << "fd is " << fd;

        std::cout.flush();

        std::cout.flush();

        return true;

    }

    void send(char *data, int len)
    {
        int rlen = 0;

        rlen = sendto(fd, data, len, 0, (struct sockaddr *)&myaddr, sizeof(myaddr));
        std::cout << "rlen is " << errno;

    }

    void stop_client()
    {
        close(fd);
    }

};
