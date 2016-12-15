#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <cstdio>

int main()
{
    int sockfd = 0;
    int num = 0;
    char recvbuffer[1000];
    struct sockaddr_in add;
    memset(recvbuffer, '0', sizeof(recvbuffer));
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "CREATE SOCKET FAILED" << std::endl;
        return 1;
    }
    add.sin_family = AF_INET;
    add.sin_port = htons(5000);
    add.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*) &add, sizeof(add)) < 0) {
        std::cout << "CONNECT FAILED" << std::endl;
        return 2;
    }

    while ((num = read(sockfd, recvbuffer, sizeof(recvbuffer) - 1)) > 0) {
        recvbuffer[num] = 0;
        if (fputs(recvbuffer, stdout) < 0) {
            std::cout << "fputs FAILED" << std::endl;
        }
        std::cout << std::endl;
    }

    if (num < 0) {
        std::cout << "READ FAILED" << std::endl;
    }

    return 0;
}
