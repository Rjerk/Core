#include "utility.h"

int main(int argc, char** argv)
{
	if (argc != 2) {
		printf ("usage: ./client [port].\n");
		return -1;
	}
	struct sockaddr_in clnt_add;
	clnt_add.sin_family = AF_INET;
	clnt_add.sin_port = htons(atoi(argv[1]));
	clnt_add.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return -1;

	if (connect(sock, (struct sockaddr*)&clnt_add, sizeof(clnt_add)) < 0)
		return -1;

	int pipefd[2];
	if (pipe(pipefd) < 0)
		return -1;

	int epfd = epoll_create(10);
	static epoll_event events[2];
	addfd(epfd, sock, true);
	addfd(epfd, pipefd[0], true);

	bool isOnline = true;
	char msg[BUF_SIZE];

	int pid = fork();
	if (pid < 0) {
		return -1;
	} else if (pid == 0) {
		close(pipefd[0]);

		while (isOnline) {
			bzero(&msg, BUF_SIZE);
			fgets(msg, BUF_SIZE, stdin);

			if (strncasecmp(msg, "QUIT", 4) == 0) {
				isOnline = false;
			} else {
				if (write(pipefd[1], msg, strlen(msg)) < 0)
					return -1;
			}
		}
	} else {
		close(pipefd[1]);

		while (isOnline) {
			int epoll_event_count = epoll_wait(epfd, events, 2, -1);

			for (int i = 0; i < epoll_event_count; ++i) {
				bzero(&msg, BUF_SIZE);
				if (events[i].data.fd == sock) { // receive message from server.
					int ret = recv(sock, msg, BUF_SIZE, 0);
					if (ret == 0) {
						printf ("Server close the connection");
						close(sock);
						isOnline = false;
					} else if (ret > 0) {
						printf ("%s\n", msg);
					} else {
						return -1;
					}
				} else { // recevie message from child process.
					int ret = read(events[i].data.fd, msg, BUF_SIZE);
					if (ret == 0) {
						isOnline = 0;
					} else if (ret > 0) {
						if (send(sock, msg, BUF_SIZE, 0) < 0) {
							return -1;
						}
					} else {
						return -1;
					}

				}
			}
		}
	}

	if (pid == 0) {
		close(pipefd[1]);
	} else {
		close(pipefd[0]);
		close(sock);
	}
}
