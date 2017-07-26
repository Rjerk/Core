#include "unp.h"

const int NDG = 2000; // datagram to send.
const int DGLEN = 4000; // length of each datagram.

void dg_clnt(FILE*, int sockfd, const SA* pservaddr, socklen_t serv_len)
{
    char sendline[DGLEN];

    for (int i = 0; i < NDG; ++i) {
        Sendto(sockfd, sendline, DGLEN, 0, pservaddr, serv_len);
    }
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        err_quit("usage: ./udpclnt04 <ip> <port>");
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    dg_clnt(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

    exit(0);
}
