#ifndef CRAWLER_H
#define CRAWLER_H

#include <epoll>
#include "dns.h"
#include "url.h"

class Crawler {
public:
    Crawler();
    ~Crawler();
    void start();
private:
    void fetch();
    void initCrawler();
    void initEpoll();
    void run(void* arg);
    void fetch();
    void epollEventHandle();
    int fetchURL(string& url);
    int makeConn(int* connfd);
    int prepareRequest(char* buffer, int* size, const string& url);
private:
    int conn_num;
    int epfd;
    struct epoll_event* events;
    DNS dns_manager;
    URL url_processor;
    struct CrawlerState {
        int fd;
        int state;
        char* base;
        char* html_body;
        int len;
        int last;
    };
};

#endif
