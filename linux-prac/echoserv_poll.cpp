#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <poll.h>

#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include <cstring>

#include <vector>
#include <iostream>

#define ERR_EXIT(m) \
    do { perror(m); exit(EXIT_FAILURE); } while (0);

using pollfd_vec = std::vector<struct pollfd>;

int main()
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    int idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
    int listenfd;
    if ((listenfd = socket(PF_INET,
                    SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,
                    IPPROTO_TCP)) < 0) {
        ERR_EXIT("socket");
    }
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET,
                   SO_REUSEADDR, &on, sizeof(on)) < 0) {
        ERR_EXIT("setsockopt");
    }

    if (bind(listenfd, (struct sockaddr*)&servaddr,
                       sizeof(servaddr)) < 0) {
        ERR_EXIT("bind");
    }
    if (listen(listenfd, SOMAXCONN) < 0) {
        ERR_EXIT("listen");
    }

    struct pollfd pfd;
    pfd.fd = listenfd;
    pfd.events = POLLIN;

    pollfd_vec pollfds;
    pollfds.push_back(pfd);

    int nready;
    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int connfd;

    while (true) {
        nready = poll(pollfds.data(), pollfds.size(), -1);
        if (nready == -1) {
            if (errno == EINTR) {
                continue;
            }
            ERR_EXIT("poll");
        } else if (nready == 0) { // nothing happened.
            continue;
        }

        if (pollfds[0].revents & POLLIN) {
            peerlen = sizeof(peeraddr);
            connfd = accept4(listenfd, (struct sockaddr*)&peeraddr,
                            &peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
            if (connfd == -1) {
                if (errno == EMFILE) {
                    close(idlefd);
                    idlefd = accept(listenfd, NULL, NULL);
                    close(idlefd);
                    idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
                    continue;
                } else {
                    ERR_EXIT("accept4");
                }
            }

            pfd.fd = connfd;
            pfd.events = POLLIN;
            pfd.revents = 0;
            pollfds.push_back(pfd);
            --nready;

            std::cout << "ip = " << inet_ntoa(peeraddr.sin_addr)
                      << " port = " << ntohs(peeraddr.sin_port) << std::endl;

            if (nready == 0) {
                continue;
            }
        }

        for (pollfd_vec::iterator it = pollfds.begin()+1;
                    it != pollfds.end() && nready > 0; ++it) {
            if (it->revents & POLLIN) {
                --nready;
                connfd = it->fd;
                char buf[1024] = { 0 };
                int ret = read(connfd, buf, 1024);
                if (ret == -1) {
                    ERR_EXIT("read");
                } else if (ret == 0) {
                    std::cout << "client close." << std::endl;
                    it = pollfds.erase(it);
                    --it;
                    close(connfd);
                    continue;
                }

                std::cout << buf;
                write(connfd, buf, strlen(buf));
            }
        }
    }
}
