#include "server.h"

int main()
{
    Server server(4000, 10);
    server.runServer();

    return 0;
}
