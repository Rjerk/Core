#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

std::list<int> clients_list;

const size_t BUF_SIZE = 1024;

int setNonBlocking(int sock)
{
	fcntl(sock, F_SETFL, fcntl(sock, F_GETFD, 0) | O_NONBLOCK);
	return 0;
}

void addfd(int epfd, int fd, bool enable_et)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if (enable_et)
		ev.events |= EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
	setNonBlocking(fd);
	printf ("fd added to epoll\n");
}

int sendBroadcastMsg(int clntfd)
{
	char buf[BUF_SIZE];
	char msg[BUF_SIZE];
	bzero(buf, BUF_SIZE);
	bzero(msg, BUF_SIZE);

	int len = recv(clntfd, buf, BUF_SIZE, 0);

	if (len == 0) {
		close(clntfd);
		clients_list.remove(clntfd);
		printf ("client id = %d closed.\n", clntfd);
	} else {
		if (clients_list.size() == 1) {
			const char* respond =  "Only one client is in this room.";
			send(clntfd, respond, strlen(respond), 0);
			return len;
		}

		sprintf (msg, "clientID:%d> %s", clntfd, buf);

		for (std::list<int>::const_iterator iter = clients_list.cbegin();
					iter != clients_list.cend(); ++iter) {
			if (*iter != clntfd) {
				if (send(*iter, msg, BUF_SIZE, 0) < 0)
					return -1;
			}
		}
	}
	return len;
}

#endif