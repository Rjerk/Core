#include "../../unp.h"

ssize_t Dg_send_recv(int, const void*, size_t, void*, size_t, const SA*, socklen_t);

void dg_clnt(FILE* fp, int sockfd, const SA* pservaddr, socklen_t servlen)
{
    ssize_t n;
    char sendline[MAXLINE], recvline[MAXLINE];

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        printf("input: %s\n", sendline);

        n = Dg_send_recv(sockfd, sendline, strlen(sendline),
                        recvline, MAXLINE, pservaddr, servlen);
        recvline[n] = 0;
        printf("recvline: %s\n", recvline);
        Fputs(recvline, stdout);
    }
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        err_quit("usage: ./udpclnt01 <ip> <port>");
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    printf("sockfd: %d\n", sockfd);

    dg_clnt(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

    exit(0);
}
