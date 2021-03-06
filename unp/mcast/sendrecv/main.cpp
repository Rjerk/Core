#include "../../unp.h"

void recv_all(int, socklen_t);
void send_all(int, SA *, socklen_t);

int main(int argc, char** argv)
{
    if (argc != 3) {
        // ./sendrecv 239.255.1.2 8888
        err_quit("usage: ./sendrecv <IP-multicast-address> <port>");
    }

    socklen_t salen;
    struct sockaddr *sasend = NULL, *sarecv = NULL;

    int sendfd = Udp_client(argv[1], argv[2], (SA **) &sasend, &salen);
    int recvfd = Socket(sasend->sa_family, SOCK_DGRAM, 0);
    int on = 1;
    Setsockopt(recvfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    sarecv = (struct sockaddr *) Malloc (salen);
    memcpy(sarecv, sasend, salen);

    Bind(recvfd, sarecv, salen);

    Mcast_join(recvfd, sasend, salen, NULL, 0);
    Mcast_set_loop(sendfd, 0);

    if (Fork() == 0) {
        recv_all(recvfd, salen);
    }

    send_all(sendfd, sasend, salen);
}
