#include <sys/types.h>  //
#include <sys/socket.h> //use socket
#include <netinet/in.h> //use struct sockaddr_in
#include <cstring>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <cerrno>

int main()
{
    int listenfd = 0;
    int connectfd = 0;
    int num;
    struct sockaddr_in servaddr;
    char sendbuffer[1000];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "SERVER RETRIEVE SUCCESS" << std::endl;

    memset(&servaddr, '0', sizeof(servaddr));
    memset(sendbuffer, '0', sizeof(sendbuffer));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000); //host to network short
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //host to network long

    bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    if (listen(listenfd, 20) < 0) {
        std::cout << "LISTEN FAILED" << std::endl;
        return 1;
    }

    while (1) {
        connectfd = accept(listenfd, (struct sockaddr*) NULL, NULL);
        //copy a string to sendbuffer
        strcpy(sendbuffer, "This is a message from server\nPass a message to client\n");
        //write
        write(connectfd, sendbuffer, strlen(sendbuffer));

        close(connectfd);
    }

    return 0;
}

