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

#define BUF_SIZE 100

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf ("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    struct hostent* host = gethostbyname(argv[1]);
    int clntSock;
    int server_port = atoi(argv[2]);
    struct sockaddr_in sendSockAddr;
    char message[BUF_SIZE];

    const int nbufs = 10;
    const int bufsize = 150;
    char databuf[nbufs][bufsize];

    int repetition = 5;
    while (repetition--) {
    clntSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clntSock == -1) {
        printf ("socket() error\n");
        exit(2);
    }

    bzero((void*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
        inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(server_port);

    if (connect(clntSock, (struct sockaddr*)&sendSockAddr, sizeof(sendSockAddr)) == -1) {
        printf ("connect() error\n");
        exit(2);
    }

    while (1) {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        int str_len = write(clntSock, message, strlen(message));
        int recv_len = 0;
        while (recv_len < str_len) {
            int recv_cnt = read(clntSock, &message[recv_len], BUF_SIZE-1);
            if (recv_cnt == -1) {
                printf ("read() error");
                exit(3);
            }
            recv_len += recv_cnt;
        }
        message[str_len] = '\0';
        printf ("Message from server: %s", message);
    }
    close(clntSock);
    }
}
