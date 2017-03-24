#include "err.h"

class Server {
    friend void Receive(int);
public:
    Server();
    Server(int, int);
    ~Server();
    void runServer();
private:
    bool CheckArg();
    int port;
    int reps;
	int servSock;
};
