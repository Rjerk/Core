#include <cstdio>
#include <cstdlib>
#include <sys/types.h>    // socket, bind
#include <sys/socket.h>   // socket, bind, listen, inet_ntoa
#include <netinet/in.h>   // htonl, htons, inet_ntoa
#include <arpa/inet.h>    // inet_ntoa
#include <netdb.h>        // gethostbyname
#include <unistd.h>       // read, write, close
#include <string.h>       // bzero
#include <netinet/tcp.h>  // SO_REUSEADDR
#include <sys/uio.h>      // writev

#define BUF_SIZE 1500

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf ("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    char message[BUF_SIZE];
    sockaddr_in servSockAddr;
    bzero((void*)&servSockAddr, sizeof(servSockAddr));
    servSockAddr.sin_family = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servSockAddr.sin_port = htons(atoi(argv[1]));

    int servSock = socket(AF_INET, SOCK_STREAM, 0);
    if (servSock == -1) {
        printf ("socket() error\n");
        exit(2);
    }
    const int on = 1;
    if (setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(int))) {
        printf ("setsockopt() error\n");
        exit(3);
    }

    if (bind(servSock, (sockaddr*) &servSockAddr, sizeof(servSockAddr)) == -1) {
        printf ("bind() error\n");
        exit(4);
    }

    if (listen(servSock, 5) == -1) {
        printf ("listen() error\n");
        exit(5);
    }

    sockaddr_in clntSockAddr;
    for (int i = 0; i < 5; ++i) {
        socklen_t clntSockAddrSize = sizeof(clntSockAddr);
        int clntSock = accept(servSock, (sockaddr*) &clntSockAddr, &clntSockAddrSize);
        if (clntSock == -1) {
            printf ("accept() error\n");
            exit(6);
        } else {
            printf ("Connected client %d\n", i+1);
        }
        int n;
        while ((n = read(clntSock, message, BUF_SIZE)) > 0) {
            write(clntSock, message, n);
        }
        if (n == -1) {
            printf ("read() error\n");
            exit(7);
        }
        close(clntSock);
    }
    close(servSock);
}
