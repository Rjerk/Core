#include "err.h"
#include <cstdio>
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
#include <sys/wait.h>     // waitpid

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf ("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    sockaddr_in servSockAddr;
    bzero((void*)&servSockAddr, sizeof(servSockAddr));
    servSockAddr.sin_family = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servSockAddr.sin_port = htons(atoi(argv[1]));

    int servSock = socket(AF_INET, SOCK_STREAM, 0);
    if (servSock == -1)
        error_Exit("socket() error!");

    const int on = 1;
    if (setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR,
                (void*) &on, sizeof(int)) == -1)
        error_Exit("setsockopt() error!");

    if (bind(servSock, (sockaddr*)&servSockAddr,
                sizeof(servSockAddr)) == -1)
        error_Exit("bind() error!");

    if (listen(servSock, 5) == -1)
        error_Exit("listen() error!");

    while (true) {
    	sockaddr_in connSockAddr;
        socklen_t len = sizeof(connSockAddr);
        int connSock = accept(servSock, (sockaddr*) &connSockAddr, &len);
		int pid;
        if ((pid = fork()) < 0) {
            error_Exit("fork() error!");
		} else if (pid > 0) {
            close(connSock);
        } else if (pid == 0) {
            if (getpeername(connSock, (sockaddr*) &connSockAddr, &len) == -1)
                error_Exit("getpeername() error!");

			char clntIP[INET_ADDRSTRLEN];
            const char* ptr = NULL;
            if ((ptr = inet_ntop(AF_INET, &connSockAddr.sin_addr, clntIP, sizeof(clntIP))) == NULL)
                error_Exit("inet_ntop() error!");

            uint16_t clntPort = ntohs(connSockAddr.sin_port);
            printf ("client addr = %s ", clntIP);
            printf ("port = %d\n", clntPort);

            unsigned int ipAddr = inet_addr(clntIP);
            struct hostent* ht = NULL;
            if ((ht = gethostbyaddr((const void*) &ipAddr, sizeof(unsigned int), AF_INET)) == NULL)
                error_Exit("gethostbyaddr() error!\nA spooling client!\n");

            printf ("official name of host: %s, ", ht->h_name);
            printf ("\nalias list: ");
            for (int i = 0; ; ++i) {
                if (ht->h_aliases[0] == NULL) {
                    printf ("none\n");
                    break;
                }
				if (ht->h_aliases[i] != NULL) {
                	printf ("%s\t", ht->h_aliases[i]);
				} else {
					break;
				}
            }

			in_addr *addrList;
            int addrListSize;
            char *reg_ip;

            for (addrListSize = 0; (addrList = (in_addr *)ht->h_addr_list[addrListSize]) != NULL; addrListSize++) {
            	reg_ip = inet_ntoa(*addrList);
            	std::cout << "ip address: " << reg_ip << " ... hit! " << std::endl;
            }

			char* ip = inet_ntoa(connSockAddr.sin_addr);
			bool honestClient = false;
            for (int i = 0; i <= addrListSize; i++) {
            	if (ip == reg_ip) {
                	honestClient = true;
                    break;
                }
            }
			if (honestClient) {
				printf ("an honest client\n");
			} else {
				printf ("a spoofing client\n");
			}
			close(connSock);
			exit(0);
        }
    }
    close(servSock);
}
