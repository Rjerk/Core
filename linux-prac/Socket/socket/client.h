#include <string>

class Client {
public:
    Client();
    ~Client();
    Client(std::string, int, int, int, int, int);
    void runTest();
private:
    int Connect();
    void MultipleWrites(int);
    void Writev(int);
    void SingleWrite(int);
    bool CheckArg();
private:
    std::string serverIP;
    int port;
    int rep;
    int nbufs;
    int bufsize;
    int type;
};
