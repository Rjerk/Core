#include "../unp.h"

int main(int argc, char** argv)
{
    if (argc != 3) {
        err_quit("usage: ./tcpsend05 <host> <port#>");
    }

    int sockfd = Tcp_connect(argv[1], argv[2]);

    int size = 32768;
    Setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size));

    char buf[16384];
    Write(sockfd, (void *) buf, 16384);
    printf("wrote 16384 bytes of normal data\n");
    sleep(5);

    Send(sockfd, "a", 1, MSG_OOB);
    printf("wrote 1 bytes of OOB data\n");

    Write(sockfd, (void *) buf, 1024);
    printf("wrote 1024 byte of normal data\n");

    exit(0);
}
