#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <iostream>

class udp_server {
 private:
    unsigned int port;
    const int domain = AF_INET;
    const int type = SOCK_DGRAM;
    struct in_addr sin_addr;
    int fd;

 public:
     udp_server(int port, in_addr_t addr) {
        this->port = port;
        this->sin_addr.s_addr = addr;
    } bool start_server() {
        int rv;
        std::cout.flush();
        std::cout << "starting server";
        fd = socket(domain, type, 0);

        if (fd < 0) {
            std::cout << "socket system call failed\n";
            return false;
        } else
            std::cout << "fd is " << fd;

        std::cout.flush();
        struct sockaddr_in myaddr;
        myaddr.sin_family = AF_INET;
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        myaddr.sin_port = htons(port);

        rv = bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr));
        if (rv < 0) {
            std::cout << "bind system call failed\n " << errno;
            return false;
        } else
            std::cout << "bind succeeded";
        std::cout.flush();

        std::cout << "starting server on port " << port;
        char buf[65536];
        struct sockaddr_in remaddr;     /* remote address */
        socklen_t addrlen = sizeof(remaddr);    /* length of addresses */
        int len = 0;
        for (;;) {
            len = recvfrom(fd, buf, 65536, 0, (struct sockaddr *)&remaddr, &addrlen);

            if (len > 0) {
                std::cout << "Received bytes " << len << " Data is " << std::endl;
            }
        }
        return true;

    }

    void stop_server() {
        close(fd);
    }

};
