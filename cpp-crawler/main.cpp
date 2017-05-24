#include "server.h"
#include "clawler.h"

int main()
{
    Server server;
    server.run();

    Crawler crawler;
    crawler.start();
}
