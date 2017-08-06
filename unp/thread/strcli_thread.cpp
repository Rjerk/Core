#include "unpthread.h"

static int sockfd;
static FILE* fp;

void* copyto(void *)
{
    char sendline[MAXLINE];
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Writen(sockfd, sendline, strlen(sendline));
    }

    Shutdown(sockfd, SHUT_WR);

    return NULL;
}

void str_cli(FILE* fp_arg, int sockfd_arg)
{
    char recvline[MAXLINE];
    pthread_t tid;

    sockfd = sockfd_arg;
    fp = fp_arg;

    Pthread_create(&tid, NULL, copyto, NULL);
    printf("pthread created.\n");
    while (Readline(sockfd, recvline, MAXLINE) > 0) {
        Fputs(recvline, stdout);
    }
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        err_quit("usage: ./cli <hostname> <service>");
    }

    int sock = Tcp_connect(argv[1], argv[2]);

    str_cli(stdin, sock);

    exit(0);
}
