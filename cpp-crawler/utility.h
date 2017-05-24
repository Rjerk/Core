#ifndef UTILITY_H
#define UTILITY_H

#include <fcntl.h>
#include <iostream>

using namespace std;

int setNonblocking(int fd)
{
    int oldflags = fcntl(fd, F_GETFD, 0);
    assert(oldflags != -1);
    int newflags = oldflags | O_NONBLOCK;
    int ret = fcntl(fd, F_SETFL, &newflags);
    assert(ret != -1);
    return 0;
}

int isValidHTML(char* html, int size)
{
    char* pcl_pos;
    html[size] = '\0';
    if ((pcl_pos = strstr(html, "Content-Length: ")) == NULL)
        return -1;
    int content_len = atoi(p + strlen("Content-Length: "));
    cout << "Content-Length: " << content_len << "\n";

    char* pcrlf = strstr(html, "\r\n\r\n");
    if (pcrlf == NULL)
        return -1;
    int len = pcrlf - html + strlen("\r\n\r\n") + content_len;
    if (size < len)
        return -1;
    if (size > len)
        cerr << "size: " << size << " len: " << len << "\n";
    return 0;
}


#endif
