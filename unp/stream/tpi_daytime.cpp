#include "tpi_daytime.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_quit("usage: ./tpi_daytime <IPAddress>");
    }

    int fd = Open(XTI_TCP, O_RDWR, 0);

    struct sockaddr_in myaddr, servaddr;
    bzero(&myaddr, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(0);

    tpi_bind(fd, &myaddr, sizeof(struct sockaddr_in));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    tpi_connect(fd, &servaddr, sizeof(struct sockaddr_in));

    int n;
    char recvline[MAXLINE];
    for ( ; ; ) {
        if (( n = tpi_read(fd, recvline, MAXLINE)) <= 0) {
            if (n == 0) {
                break;
            } else {
                err_sys("tpi_read error");
            }
        }
        recvline[n] = 0;
        fputs(recvline, stdout);
    }

    tpi_close(fd);
    exit(0);
}
