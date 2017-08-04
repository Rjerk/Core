#include "../unp.h"

const int QSIZE =    8; // size of input queue.
const int MAXDG = 4096; // max datagram size.

using DG = struct {
    void*            dg_data;  // ptr to actual datagram.
    size_t           dg_len;   // length of datagram.
    struct sockaddr* dg_sa;    // ptr to sockaddr{} w/client's address.
    socklen_t        dg_salen; // length of sockaddr{}.
};

static int sockfd;
static DG dg[QSIZE]; // queue of datagram to process.
static long cntread[QSIZE+1]; // diagnostic counter.

static int iget; // next one for main loop to process.
static int iput; // next one for signal handler to read into.
static int nqueue; // # on queue for main loop to process.
static socklen_t clilen; // max length of sockaddr{}.

static void sig_io(int)
{
    ssize_t len;
    int nread;
    DG* ptr;

    for (nread = 0; ; ) {
        if (nqueue >= QSIZE) {
            err_quit("receive overflow");
        }

        ptr = &dg[iput];
        ptr->dg_salen = clilen;
        len = recvfrom(sockfd, ptr->dg_data, MAXDG, 0,
                       ptr->dg_sa, &ptr->dg_salen);
        if (len < 0) {
            if (errno == EWOULDBLOCK) {
                break;
            } else {
                err_sys("recvfrom error");
            }
        }
        ptr->dg_len = len;

        ++nread;
        ++nqueue;
        if (++iput >= QSIZE) {
            iput = 0;
        }
    }
    ++cntread[nread];
}

void dg_echo(int sockfd_arg, SA*, socklen_t clilen_arg)
{
    sockfd = sockfd_arg;
    clilen = clilen_arg;

    for (int i = 0; i < QSIZE; ++i) { // init queue of buffers.
        dg[i].dg_data = Malloc(MAXDG);
        dg[i].dg_sa = (struct sockaddr*) Malloc(clilen);
        dg[i].dg_salen = clilen;
    }

    iget = iput = nqueue = 0;

    //Signal(SIGHUP, sig_hup);
    Signal(SIGHUP, [] (int) {
        for (int i = 0; i <= QSIZE; ++i) {
            printf("cntread[%d] = %ld", i, cntread[i]);
        }
    });
    Signal(SIGIO, sig_io);
    Fcntl(sockfd, F_SETOWN, getpid());
    auto flags = fcntl(sockfd, F_GETFL);
    Fcntl(sockfd, F_SETFL, flags | O_ASYNC | O_NONBLOCK);

    sigset_t zeromask, newmask, oldmask;
    Sigemptyset(&zeromask);
    Sigemptyset(&newmask);
    Sigemptyset(&oldmask);
    Sigaddset(&newmask, SIGIO); // signal we want to block.
    Sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    for ( ; ; ) {
        while (nqueue == 0) {
            sigsuspend(&zeromask); // wait for datagram to process.
        }

        // unblock SIGIO.
        Sigprocmask(SIG_SETMASK, &oldmask, NULL);

        Sendto(sockfd, dg[iget].dg_data, dg[iget].dg_len, 0,
               dg[iget].dg_sa, dg[iget].dg_salen);

        if (++iget >= QSIZE) {
            iget = 0;
        }

        Sigprocmask(SIG_BLOCK, &newmask, &oldmask);
        --nqueue;
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) {
            err_quit("usage: ./udpserv01 <port>");
        }
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr, clntaddr;
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SA *) &clntaddr, sizeof(clntaddr));
}
