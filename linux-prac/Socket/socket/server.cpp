#include "server.h"
#include "err.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <sys/time.h>     // timeval
#include <sys/types.h>    // socket, bind
#include <sys/socket.h>   // socket, bind, listen, inet_ntoa
#include <netinet/in.h>   // htonl, htons, inet_ntoa
#include <arpa/inet.h>    // inet_ntoa
#include <netdb.h>        // gethostbyname
#include <unistd.h>       // read, write, close
#include <string.h>       // bzero
#include <netinet/tcp.h>  // SO_REUSEADDR
#include <sys/uio.h>      // writev
#include <signal.h>       // signal
#include <fcntl.h>        // fcntl

const int BUFSIZE = 1500;
int clntSock;
int rept;

Server::Server()
{
}

Server::~Server()
{
	close(clntSock);
	close(servSock);
}

Server::Server(int _port, int _reps):
    port(_port), reps(_reps)
{
    rept = reps;
    if (!CheckArg())
        error_Exit("Arguments error!");
}

void Receive(int signo)
{
    char databuf[BUFSIZE];
    int call_read_times = 0;
    int inRead = 0;
    for (int i = 1; i <= rept; ++i) {
        std::cout << "reps: " << i << std::endl;
        while (inRead < BUFSIZE) {
            int bytesRead = read(clntSock, databuf, BUFSIZE-inRead);
            if (bytesRead == -1)
                error_Exit("read() error!");
            inRead += bytesRead;
            ++call_read_times;
        }
    }
    std::cout << "call_read_times: " << call_read_times << std::endl;
	if (write(clntSock, &call_read_times, sizeof(call_read_times)) == -1)
		error_Exit("write() error!");
	sleep(1);
	exit(0);
}

void Server::runServer()
{
	sockaddr_in servSockAddr;
    bzero((void*)&servSockAddr, sizeof(servSockAddr));
    servSockAddr.sin_family = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servSockAddr.sin_port = htons(port);

    servSock = socket(AF_INET, SOCK_STREAM, 0);
    if (servSock == -1)
        error_Exit("socket() error!");
    const int on = 1;
    if (setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR,
                        (void*) &on, sizeof(int)) == -1)
        error_Exit("setsockopt() error!");

    if (bind(servSock, (sockaddr*)&servSockAddr, sizeof(servSockAddr)) == -1)
        error_Exit("bind() error!");

    if (listen(servSock, 12) == -1)
        error_Exit("listen() error!");

	sockaddr_in clntSockAddr;
	socklen_t len = sizeof(clntSockAddr);
	clntSock = accept(servSock, (sockaddr*) &clntSockAddr, &len);
	 if (clntSock == -1)
	     error_Exit("accept() error!");
	if (signal(SIGIO, Receive) == SIG_ERR)
		    error_Exit("Cound not establish hanlder for SIGIO!");
	fcntl(clntSock, F_SETOWN, getpid());
	fcntl(clntSock, F_SETFL, FASYNC);
  	while (true) pause();
}

bool Server::CheckArg()
{
    if (port < 1024) {
        error_Exit("port should be larger than 1023!");
        return false;
    }
    if (reps < 0) {
        error_Exit("reps should be larger than 0");
        return false;
    }
    return true;
}
