#include "crawler.h"
#include <fstream>
#include <string>
#include <cassert>
#include <set>
#include <queue>
#include <pthread>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using std::string;
using std::ifstream;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

std::queue<string> unvisited_url_queue;
std::set<string> visited_url_set;

const int MAXLINE = 100;

Crawler::Crawler():
    conn_num(0)
{
    initCrawler();
    initEpoll();
}

Crawler::~Crawler()
{
}

void Crawler::initCrawler()
{
    string oneline;
    ifstream infile(SEED_FILE.c_str(), ios::binary);
    assert(infile.good());
    while (getline(infile, oneline))
        unvisited_url_queue.push_back(oneline);
    infile.close();

    infile.open(VISITED_URL.c_str(), ios::binary);
    assert(infile.good());
    while (getline(infile, oneline))
        visited_url_set.push_back(oneline);
    infile.close();
}

void Crawler::initEpoll()
{
    int fd = epoll_create1(0);
    assert(fd > 0);
    event = (struct epoll_event*) malloc
                (sizeof(struct epoll_event) * MAXEVENTS);
    epfd = fd;
}

void Crawler::start()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, run, this);
    assert(ret > 0);
    pthread_join(tid, NULL);
}

void Crawler::run(void* arg)
{
    ((Crawler*)arg)->fetch();
}

void Crawler::fetch()
{
    int ret = 0;
    string url;
    int connfd;
    int size;
    char req_buffer[MAXLINE];
    while (true) {
        do {
            // get url from unvisited_url
            if (conn_num < MAXCONN) {
                ret = fetchURL(url);
                assert(ret == 0);
		        // make connection to url and get connect-fd
		        ret = makeConn(&connfd);
		        assert(ret == 0);
		        // prepare the header and body to buffer
		        // and ready to write to server
		        ret = prepareRequest(req_buffer, &size, url);
		        assert(ret == 0);
		        // write request to fd
		        ret = write(connfd, req_buffer, size);
		        assert(ret == 0);
		        // initialize clawler's state.
		        CrawlerState* pstate = new CrawlerState;
		        pstate->fd = connfd;
		        pstate->state = 0;
		        memcpy(pstate->base, url.c_str(), url.size());
		        pstate->len = url.size();
		        pstate->last = 0;
		        // epoll event control, set edge-trigger.
		        struct epoll_event event;
		        event.data.ptr = (void*) pstate;
		        event.events = EPOLLIN | EPOLLET;
		        ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
		        assert(ret == 0);
		        // make a new connection.
		        ++conn_num;
            }
        } while (0);

        epollEventHandle();

    };
}

void Crawler::epollEventHandle()
{
    int num = epoll_wait(epfd, events, MAXEVENTS, EPOLLTIMEOUT);
    assert(num >= 0);
    int ret = 0;
    Crawler* pstate;
    for (int i = 0; i < num; ++i) {
        pstate = (Crawler*) events[i].data.ptr;
        int header_size = MAXLINE;
        vector<string> followers_vec;

        switch (pstate->state) {
            case 0:
                // get respond from server.
                ret = getRespond(pstate);
                assert(ret != 0);
                // parse html
                ret = isValidHTML(pstate->html_body, pstate->last);
                assert(ret != 0);
                Parser::searchFollers(pstate->html_body, pstate->last, followers_vec);
                // push url to followers vector.

        }
    }
}

int Crawler::getRespond(CrawlerState* pstate)
{
    int fd = pstate->fd;
    int last = pstate->last;
    int ret = 0;
    int nread = 0;
    int first = 0;

    while (true) {
        nread = read(fd, pstate->html_body + last, HTMLSIZE - last);

        if (nread == 0) {
            if (first)
                cout << "first loop read EOF\n";
            else
                cout << "not first loop read EOF\n";
        } else if (nread < 0) {
            if (errno != EGAIN) { // server close the connection.
                cerr << "errno: " << errno << "\n";
                close(fd);
                --conn_num;
                return -1;
            }
        }
        last += nread;
        first = 0;
    }
    pstate->last = last;
    return ret;
}


int Crawler::fetchURL(string& url)
{
    int ret = 0;
    int i;
    while (true) {
        if (unvisited_url_queue.empty()) {
            cout << "thread id: "
                << (long)pthread_self() % THREADNUM << "\n";
            return -1;
        }
        url = unvisited_url_queue.front();
        unvisited_url_queue.pop();
        break;
    }
    logInfo("fetch a url: ", url);
    return 0;
}

int Crawler::makeConn(int* connfd)
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock > 0);

    struct hostent* server;
    struct sockaddr_in serv_addr;
    string ip = dns_manager.getIP(url_processer.getHost());

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);
    serv_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    ret = setNonblocking(sock);
    assert(ret != -1);

    ret = connect(sock, (struct socaddr*) serv_addr, sizeof(serv_addr);
    assert(ret == 0);

    *fd = sock;
    return ret;
}

int Crawler::prepareRequest(char* buffer, int* size, const string& url)
{
    URL url_parser(url);
    int ret = 0;
    ret = snprintf(buffer, *size,
            "GET %s/answers?order_by=vote_num HTTP/1.1\r\n"
            "Host: www.zhihu.com\r\n"
            "Connection: keep-alive\r\n"
            "Cache-Control: max-age=0\r\n"
            "Accept: text/html,application/xhtml+xml,application/xml;"
                "q=0.9,image/webp,*/*;q=0.8\r\n"
            "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5)"
                "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157"
                "Safari/537.36\r\n"
            "Content-Type: application/x-www-form-urllencoded; charset=UTF-8\r\n"
            "Referer: %s/followers\r\n"
            "Accept-Language: zh-CN,zh;q=0.8\r\n"
            "Cookie: %s\r\n"
            "\r\n"
            "%s"
            url_parser.getPath().c_str(), cookie.c_str(), post_body);
    assert(ret > 0);
    *size = ret;
    return 0;
}

int Crawler::getFollowerURLRespond()
{

}
