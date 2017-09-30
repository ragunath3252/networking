#include <iostream>
#include "server.h"
#include "client.h"
#include <string.h>
#include <netdb.h>
int main()
{



    pid_t pid = fork();

    if(pid == 0)
    {
        sleep(2);

        udp_client *client = new udp_client(18001, "127.0.0.1");
        char data[65000];
        char test = 'c';
        for(int i=0; i<65000; i++)
        {
            data[i] = test;
        }
        client->start_client();
        for(int i=0; i<3; i++)
        {
            client->send(data, strlen(data));
            sleep(1);
        }
        std::cout.flush();
        client->stop_client();
        exit(0);
    }


    udp_server *server = new udp_server(18001, INADDR_ANY);
    if(server->start_server() == false)
        std::cout << "server start failed";

    if(pid > 0)
    {
        server->stop_server();
    }

    return 0;
}
