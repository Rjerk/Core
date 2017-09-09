#include "server.h"
#include "crawler.h"

int main()
{
    Server server;
    server.run();

    Crawler crawler;
    crawler.start();
}
