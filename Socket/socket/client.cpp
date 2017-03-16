#include "client.h"
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

Client::Client()
{
}

Client::Client(std::string _serverIP, int _port, int _rep,
				int _nbufs, int _bufsz, int _type):
    		   serverIP(_serverIP), port(_port), rep(_rep),
				nbufs(_nbufs), bufsize(_bufsz), type(_type)
{
	if (!CheckArg())
		error_Exit("Arguments Error!");
}


Client::~Client()
{
}

int Client::Connect()
{
    struct hostent* host = gethostbyname(serverIP.c_str());
    sockaddr_in sendSockAddr;
    bzero((void*)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr =
				inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);

    int clntSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clntSock == -1)
        error_Exit("socket() error!");
    if (connect(clntSock, (sockaddr*)&sendSockAddr, sizeof(sendSockAddr)) == -1)
        error_Exit("connect() error!");
    return clntSock;
}

void Client::MultipleWrites(int clntSock)
{
    std::cout << "MultipleWrites" << std::endl;
	char databuf[nbufs][bufsize];
    for (int i = 0; i < nbufs; ++i) {
        if (write(clntSock, databuf[i], bufsize) == -1)
            error_Msg("write() in MultipleWrites error!");
    }
}

void Client::Writev(int clntSock)
{
	std::cout << "Writev" << std::endl;
    struct iovec vec[nbufs];
	char databuf[nbufs][bufsize];
    for (int i = 0; i < nbufs; ++i) {
        vec[i].iov_base = databuf[i];
        vec[i].iov_len = bufsize;
    }
    if (writev(clntSock, vec, nbufs) == -1)
        error_Msg("writev() error!");
}

void Client::SingleWrite(int clntSock)
{
	std::cout << "SingleWrite" << std::endl;
	char databuf[nbufs][bufsize];
    if (write(clntSock, databuf, nbufs * bufsize) == -1)
        error_Msg("write() in SingleWrite error!");
}

void Client::runTest()
{
    std::cout << "Test:" << std::endl;
    struct timeval beg, end;

    gettimeofday(&beg, NULL);
	int clntSock = Connect();
    for (int i = 1; i <= rep; ++i) {
		std::cout << "rep: " << i << std::endl;
        switch(type) {
		    case 1:
		        MultipleWrites(clntSock);
		        break;
		    case 2:
		        Writev(clntSock);
		        break;
		    case 3:
		        SingleWrite(clntSock);
		        break;
    	}
	}
    int call_read_times;
    if (read(clntSock, &call_read_times, sizeof(call_read_times)) == -1)
        error_Msg("read() error!");
    gettimeofday(&end, NULL);

    long secs = (end.tv_sec - beg.tv_sec) * 1000000L;
    long usec = end.tv_usec - beg.tv_usec;

    std::cout << "Test #" << "round-trip time = " << (secs + usec) << " usec, "
         << "#reads = " << call_read_times << std::endl;

    close(clntSock);

}

bool Client::CheckArg()
{
    if (port < 1023) {
        error_Msg("port should be larger than 1023!");
        return false;
    }
    if (rep <= 0) {
        error_Msg("rep should be larger than 0!");
        return false;
    }
    if (nbufs * bufsize != 1500) {
        error_Msg("nbufs * bufsize != 1500!");
        return false;
    }
    if (type < 1 || type > 3) {
        error_Msg("type should be 1, 2, or 3!");
        return false;
    }
    return true;
}

