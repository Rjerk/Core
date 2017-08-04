#include	"../../unp.h"

void sig_chld(int);

void str_echo(int sockfd)
{
	heartbeat_serv(sockfd, 1, 5);

    ssize_t n;
    char line[MAXLINE];
	for ( ; ; ) {
		if ((n = Readline(sockfd, line, MAXLINE)) == 0) {
			return;
        }
		Writen(sockfd, line, n);
	}
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        err_quit("usage: ./serv <port>");
    }

	int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in clntaddr, servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	Signal(SIGCHLD, sig_chld);

    socklen_t clntlen;
    int connfd;
    pid_t childpid;
	for ( ; ; ) {
		clntlen = sizeof(clntaddr);
		if ((connfd = accept(listenfd, (SA *) &clntaddr, &clntlen)) < 0) {
			if (errno == EINTR) {
				continue;
            } else {
				err_sys("accept error");
            }
		}

		if ((childpid = Fork()) == 0) {
			Close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}
}
