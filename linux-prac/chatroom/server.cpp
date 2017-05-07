#include "utility.h"

int main(int argc, char** argv)
{
	if (argc != 2) {
		printf ("usage: ./server [port].\n");
		return -1;
	}
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		return -1;

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		return -1;

	if (listen(serv_sock, 5) == -1)
		return -1;

	int epfd = epoll_create(10);
	if (epfd == -1)
		return -1;

	static struct epoll_event events[10];
	addfd(epfd, serv_sock, true);

	for (;;) {
		int epoll_events_count = epoll_wait(epfd, events, 10, -1);
		if (epoll_events_count == -1) {
			break;
		}
		for (int i = 0; i < epoll_events_count; ++i) {
			int sockfd = events[i].data.fd;

			if (sockfd == serv_sock) {
				struct sockaddr_in clnt_addr;
				socklen_t clnt_len = sizeof(clnt_addr);

				int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_len);
				if (clnt_sock == -1)
					return -1;

				printf ("connection: %s : %d, client sock: %d\n",
						inet_ntoa(clnt_addr.sin_addr),
						ntohs(clnt_addr.sin_port),
						clnt_sock);

				addfd(epfd, clnt_sock, true);

				clients_list.push_back(clnt_sock);

				char message[BUF_SIZE];
				bzero(message, BUF_SIZE);
				sprintf (message, "Welcome to RatRoom. You get id: %d", clnt_sock);
				if (send(clnt_sock, message, BUF_SIZE, 0) == -1)
					return -1;
			} else {
				if (sendBroadcastMsg(sockfd) == -1)
					return -1;
			}
		}
	}
	close(serv_sock);
	close(epfd);
	return 0;
}
