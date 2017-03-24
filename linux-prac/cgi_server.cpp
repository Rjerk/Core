#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf ("Usage: %s <ip> <port>\n", basename(argv[0]));
        return -1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addr_len = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*) &client, &client_addr_len);

    if (connfd < 0) {
        printf ("error is: %d\n", errno);
    } else {
        close(STDOUT_FILENO);
        dup(connfd);
        sleep(3);
        printf ("1234\n"); // data was send to connfd
        close(connfd);
    }

    close(sock);
    return 0;
}
