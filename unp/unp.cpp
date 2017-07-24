#include "unp.h"
#include <errno.h>
#include <stdarg.h>
#include <arpa/inet.h>

// print a message and return to caller.
// caller specifies "errnoflag".
static void err_doit(int errnoflag, const char* fmt, va_list ap)
{
    int errno_save = errno; // value called might want printed.
    char buf[MAXLINE];
    vsprintf(buf, fmt, ap);
    if (errnoflag) {
        sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
    }
    strcat(buf, "\n");
    fflush(stdout); // in case stdout and stderr are the same.
    fputs(buf, stderr);
    fflush(stderr);
    return;
}

// fatal error unrelated to a system call.
// print a message and terminate.
void err_quit(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    exit(1);
}

// nonfatal error related to a system call.
// print a message and return.
void err_ret(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    return;
}

// fatal error related to a system call.
// print a message and terminate.
void err_sys(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    exit(1);
}

// fatal error ralated a system call.
// print a message, dump core and terminate.
void err_dump(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    abort(); // dump core and terminate.
    exit(1); // not get here.
}

// nonfatal error unrelated to a system call.
void err_msg(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    return;
}

int Socket(int family, int type, int protocol)
{
	int		n;

	if ( (n = socket(family, type, protocol)) < 0)
		err_sys("socket error");
	return(n);
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0)
		err_sys("connect error");
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		err_sys("bind error");
}

void Listen(int fd, int backlog)
{
	char	*ptr;

		/*4can override 2nd argument with environment variable */
	if ( (ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(fd, backlog) < 0)
		err_sys("listen error");
}

int Accept(int fd, struct sockaddr* sa, socklen_t* salenptr)
{
    int n;
again:
    if ((n = accept(fd, sa, salenptr) < 0)) {
#ifdef EPROTO
        if (errno == EPROTO || errno == ECONNABORTED)
#else
        if (errno == ECONNABORTED)
#endif
            goto again;
        else
            err_sys("accept error");
    }
    return (n);
}

void Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
       struct timeval *timeout)
{
	int		n;

	if ( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
		err_sys("select error");
	return(n);		/* can return 0 on timeout */
}

void Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != (ssize_t)nbytes)
		err_sys("write error");
}

ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;
	if ((n = read(fd, ptr, nbytes)) == -1) {
		err_sys("read error");
    }
	return(n);
}

const char* Inet_ntop(int family, const void *addrptr, char *strptr, socklen_t len)
{
    const char *ptr;
    if (strptr == NULL) {     /* check for old code */
        err_quit("NULL 3rd argument to inet_ntop");
    }
    if ((ptr = inet_ntop(family, addrptr, strptr, len)) == NULL) {
        err_sys("inet_ntop error");     /* sets errno */
    }
    return(ptr);
}

void Inet_pton(int family, const char *strptr, void *addrptr)
{
    int n;
    if ((n = inet_pton(family, strptr, addrptr)) < 0) {
        err_sys("inet_pton error for %s", strptr);  /* errno set */
    } else if (n == 0) {
        err_quit("inet_pton error for %s", strptr); /* errno not set */
    }
    return;
}

int Poll(struct pollfd* fdarray, unsigned long nfds, int timeout)
{
    int n;
    if ((n = poll(fdarray, nfds, timeout)) < 0) {
        err_sys("poll error");
    }
    return(n);
}

long open_max(void)
{
    long openmax = 0;
    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
        openmax = OPEN_MAX_GUESS;
    } else {
        err_sys("sysconf error for _SC_OPEN_MAX");
    }
    return(openmax);
}

