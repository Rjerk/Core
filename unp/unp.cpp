#include "unp.h"
#include <errno.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <sys/sysctl.h>

int daemon_proc; // set nonzero by deamon_init()

// print a message and return to caller.
// caller specifies "errnoflag".
static void err_doit(int errnoflag, int level, const char* fmt, va_list ap)
{
    int errno_save = errno; // value called might want printed.
    char buf[MAXLINE+1];
    vsnprintf(buf, MAXLINE, fmt, ap);
    if (errnoflag) {
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s", strerror(errno_save));
    }
    strcat(buf, "\n");
    if (daemon_proc) {
        syslog(level, buf);
    } else {
        fflush(stdout); // in case stdout and stderr are the same.
        fputs(buf, stderr);
        fflush(stderr);
    }
    return;
}

// fatal error unrelated to a system call.
// print a message and terminate.
void err_quit(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

// nonfatal error related to a system call.
// print a message and return.
void err_ret(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_INFO, fmt, ap);
    va_end(ap);
    return;
}

// fatal error related to a system call.
// print a message and terminate.
void err_sys(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(1);
}

// fatal error ralated a system call.
// print a message, dump core and terminate.
void err_dump(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, LOG_ERR, fmt, ap);
    va_end(ap);
    abort(); // dump core and terminate.
    exit(1); // not get here.
}

// nonfatal error unrelated to a system call.
void err_msg(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, LOG_INFO, fmt, ap);
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
    if ((n = accept(fd, sa, salenptr)) < 0) {
        if (errno == EPROTO || errno == ECONNABORTED)
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

const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
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

void Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	if (getpeername(fd, sa, salenptr) < 0)
		err_sys("getpeername error");
}

void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	if (getsockname(fd, sa, salenptr) < 0)
		err_sys("getsockname error");
}

void Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr)
{
	if (getsockopt(fd, level, optname, optval, optlenptr) < 0)
		err_sys("getsockopt error");
}

#ifdef	HAVE_INET6_RTH_INIT
int Inet6_rth_space(int type, int segments)
{
	int ret;

	ret = inet6_rth_space(type, segments);
	if (ret < 0)
		err_quit("inet6_rth_space error");

	return ret;
}

void* Inet6_rth_init(void *rthbuf, socklen_t rthlen, int type, int segments)
{
	void *ret;

	ret = inet6_rth_init(rthbuf, rthlen, type, segments);
	if (ret == NULL)
		err_quit("inet6_rth_init error");

	return ret;
}

void Inet6_rth_add(void *rthbuf, const struct in6_addr *addr)
{
	if (inet6_rth_add(rthbuf, addr) < 0)
		err_quit("inet6_rth_add error");
}

void Inet6_rth_reverse(const void *in, void *out)
{
	if (inet6_rth_reverse(in, out) < 0)
		err_quit("inet6_rth_reverse error");
}

int Inet6_rth_segments(const void *rthbuf)
{
	int ret;

	ret = inet6_rth_segments(rthbuf);
	if (ret < 0)
		err_quit("inet6_rth_segments error");

	return ret;
}

struct in6_addr * Inet6_rth_getaddr(const void *rthbuf, int idx)
{
	struct in6_addr *ret;

	ret = inet6_rth_getaddr(rthbuf, idx);
	if (ret == NULL)
		err_quit("inet6_rth_getaddr error");

	return ret;
}
#endif

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

ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags)
{
    ssize_t     n;

    if ( (n = recv(fd, ptr, nbytes, flags)) < 0)
        err_sys("recv error");
    return(n);
}

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags,
                 struct sockaddr *sa, socklen_t *salenptr)
{
    ssize_t     n;

    if ( (n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
        err_sys("recvfrom error");
    return(n);
}

ssize_t Recvmsg(int fd, struct msghdr *msg, int flags)
{
    ssize_t     n;
    if ( (n = recvmsg(fd, msg, flags)) < 0)
        err_sys("recvmsg error");
    return(n);
}

void Send(int fd, const void *ptr, size_t nbytes, int flags)
{
    if (send(fd, ptr, nbytes, flags) != (ssize_t)nbytes)
        err_sys("send error");
}

void Sendto(int fd, const void *ptr, size_t nbytes, int flags,
               const struct sockaddr *sa, socklen_t salen)
{
    if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
        err_sys("sendto error");
}

void Sendmsg(int fd, const struct msghdr *msg, int flags)
{
    unsigned int    i;
    ssize_t         nbytes;
    nbytes = 0; /* must first figure out what return value should be */
    for (i = 0; i < msg->msg_iovlen; i++)
        nbytes += msg->msg_iov[i].iov_len;

    if (sendmsg(fd, msg, flags) != nbytes)
        err_sys("sendmsg error");
}

void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
    if (setsockopt(fd, level, optname, optval, optlen) < 0)
        err_sys("setsockopt error");
}

void Shutdown(int fd, int how)
{
    if (shutdown(fd, how) < 0)
        err_sys("shutdown error");
}

int Sockatmark(int fd)
{
    int     n;

    if ( (n = sockatmark(fd)) < 0)
        err_sys("sockatmark error");
    return(n);
}

void Socketpair(int family, int type, int protocol, int *fd)
{
    int     n;

    if ( (n = socketpair(family, type, protocol, fd)) < 0)
        err_sys("socketpair error");
}

void Fclose(FILE *fp)
{
    if (fclose(fp) != 0)
        err_sys("fclose error");
}

FILE* Fdopen(int fd, const char *type)
{
    FILE    *fp;

    if ( (fp = fdopen(fd, type)) == NULL)
        err_sys("fdopen error");

    return(fp);
}

char* Fgets(char *ptr, int n, FILE *stream)
{
    char    *rptr;

    if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
        err_sys("fgets error");

    return (rptr);
}

FILE* Fopen(const char *filename, const char *mode)
{
    FILE    *fp;

    if ( (fp = fopen(filename, mode)) == NULL)
        err_sys("fopen error");

    return(fp);
}

void Fputs(const char *ptr, FILE *stream)
{
    if (fputs(ptr, stream) == EOF)
        err_sys("fputs error");
}

void* Calloc(size_t n, size_t size)
{
	void	*ptr;

	if ( (ptr = calloc(n, size)) == NULL)
		err_sys("calloc error");
	return(ptr);
}

void Dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		err_sys("dup2 error");
}

int Fcntl(int fd, int cmd, int arg)
{
	int	n;

	if ( (n = fcntl(fd, cmd, arg)) == -1)
		err_sys("fcntl error");
	return(n);
}

void Gettimeofday(struct timeval *tv, void *foo)
{
	if (gettimeofday(tv, (struct timezone*)foo) == -1)
		err_sys("gettimeofday error");
	return;
}

int Ioctl(int fd, int request, void *arg)
{
	int		n;

	if ( (n = ioctl(fd, request, arg)) == -1)
		err_sys("ioctl error");
	return(n);	/* streamio of I_LIST returns value */
}

pid_t Fork(void)
{
	pid_t	pid;

	if ( (pid = fork()) == -1)
		err_sys("fork error");
	return(pid);
}

void* Malloc(size_t size)
{
	void	*ptr;

	if ( (ptr = malloc(size)) == NULL)
		err_sys("malloc error");
	return(ptr);
}

/*
int Mkstemp(char *template_)
{
	int i;

#ifdef HAVE_MKSTEMP
	if ((i = mkstemp(template)) < 0)
		err_quit("mkstemp error");
#else
	if (mktemp(template_) == NULL || template_[0] == 0)
		err_quit("mktemp error");
	i = Open(template_, O_CREAT | O_WRONLY, FILE_MODE);
#endif

	return i;
}
*/

void* Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	void	*ptr;

	if ( (ptr = mmap(addr, len, prot, flags, fd, offset)) == ((void *) -1))
		err_sys("mmap error");
	return(ptr);
}

int Open(const char *pathname, int oflag, mode_t mode)
{
	int		fd;

	if ( (fd = open(pathname, oflag, mode)) == -1)
		err_sys("open error for %s", pathname);
	return(fd);
}

void Pipe(int *fds)
{
	if (pipe(fds) < 0)
		err_sys("pipe error");
}

void Sigaddset(sigset_t *set, int signo)
{
	if (sigaddset(set, signo) == -1)
		err_sys("sigaddset error");
}

void Sigdelset(sigset_t *set, int signo)
{
	if (sigdelset(set, signo) == -1)
		err_sys("sigdelset error");
}

void Sigemptyset(sigset_t *set)
{
	if (sigemptyset(set) == -1)
		err_sys("sigemptyset error");
}

void Sigfillset(sigset_t *set)
{
	if (sigfillset(set) == -1)
		err_sys("sigfillset error");
}

int Sigismember(const sigset_t *set, int signo)
{
	int		n;

	if ( (n = sigismember(set, signo)) == -1)
		err_sys("sigismember error");
	return(n);
}

void Sigpending(sigset_t *set)
{
	if (sigpending(set) == -1)
		err_sys("sigpending error");
}

void Sigprocmask(int how, const sigset_t *set, sigset_t *oset)
{
	if (sigprocmask(how, set, oset) == -1)
		err_sys("sigprocmask error");
}

char* Strdup(const char *str)
{
	char	*ptr;

	if ( (ptr = strdup(str)) == NULL)
		err_sys("strdup error");
	return(ptr);
}

long Sysconf(int name)
{
	long	val;

	errno = 0;		/* in case sysconf() does not change this */
	if ( (val = sysconf(name)) == -1)
		err_sys("sysconf error");
	return(val);
}

void Sysctl(int *name, u_int namelen, void *oldp, size_t *oldlenp,
	   void *newp, size_t newlen)
{
	if (sysctl(name, namelen, oldp, oldlenp, newp, newlen) == -1)
		err_sys("sysctl error");
}

void Unlink(const char *pathname)
{
	if (unlink(pathname) == -1)
		err_sys("unlink error for %s", pathname);
}

pid_t Wait(int *iptr)
{
	pid_t	pid;

	if ( (pid = wait(iptr)) == -1)
		err_sys("wait error");
	return(pid);
}

pid_t Waitpid(pid_t pid, int *iptr, int options)
{
	pid_t	retpid;

	if ( (retpid = waitpid(pid, iptr, options)) == -1)
		err_sys("waitpid error");
	return(retpid);
}

char* sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
    char		portstr[8];
    static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) {
	case AF_INET: {
		struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

		if (inet_ntop(AF_INET, &sin->sin_addr, str, (socklen_t)sizeof(str)) == NULL)
			return(NULL);
		if (ntohs(sin->sin_port) != 0) {
			snprintf(portstr, sizeof(portstr), ":%d", ntohs(sin->sin_port));
			strcat(str, portstr);
		}
		return(str);
	}
/* end sock_ntop */

#ifdef	IPV6
	case AF_INET6: {
		struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

		str[0] = '[';
		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str + 1, sizeof(str) - 1) == NULL)
			return(NULL);
		if (ntohs(sin6->sin6_port) != 0) {
			snprintf(portstr, sizeof(portstr), "]:%d", ntohs(sin6->sin6_port));
			strcat(str, portstr);
			return(str);
		}
		return (str + 1);
	}
#endif

#ifdef	AF_UNIX
	case AF_UNIX: {
		struct sockaddr_un	*unp = (struct sockaddr_un *) sa;

			/* OK to have no pathname bound to the socket: happens on
			   every connect() unless client calls bind() first. */
		if (unp->sun_path[0] == 0)
			strcpy(str, "(no pathname bound)");
		else
			snprintf(str, sizeof(str), "%s", unp->sun_path);
		return(str);
	}
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
	case AF_LINK: {
		struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;

		if (sdl->sdl_nlen > 0)
			snprintf(str, sizeof(str), "%*s (index %d)",
					 sdl->sdl_nlen, &sdl->sdl_data[0], sdl->sdl_index);
		else
			snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
		return(str);
	}
#endif
	default:
		snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d",
				 sa->sa_family, salen);
		return(str);
	}
    return (NULL);
}

char* Sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
	char	*ptr;

	if ( (ptr = sock_ntop(sa, salen)) == NULL)
		err_sys("sock_ntop error");	/* inet_ntop() sets errno */
	return(ptr);
}

Sigfunc* signal(int signo, Sigfunc *func)
{
	struct sigaction	act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM) {
#ifdef	SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;	/* SunOS 4.x */
#endif
	} else {
#ifdef	SA_RESTART
		act.sa_flags |= SA_RESTART;		/* SVR4, 44BSD */
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
		return(SIG_ERR);
	return(oact.sa_handler);
}
/* end signal */

Sigfunc* Signal(int signo, Sigfunc *func)	/* for our signal() function */
{
	Sigfunc	*sigfunc;

	if ( (sigfunc = signal(signo, func)) == SIG_ERR)
		err_sys("signal error");
	return(sigfunc);
}

ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	ptr = static_cast<const char*>(vptr);
	nleft = n;
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
		}

		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(n);
}
/* end writen */

void Writen(int fd, void *ptr, size_t nbytes)
{
	if (writen(fd, ptr, nbytes) != (ssize_t) nbytes)
		err_sys("writen error");
}

char* sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) {
	case AF_INET: {
		struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

		if (inet_ntop(AF_INET, &sin->sin_addr, str, (socklen_t) sizeof(str)) == NULL)
			return(NULL);
		return(str);
	}

#ifdef	IPV6
	case AF_INET6: {
		struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

		if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, (socklen_t) sizeof(str)) == NULL)
			return(NULL);
		return(str);
	}
#endif

#ifdef	AF_UNIX
	case AF_UNIX: {
		struct sockaddr_un	*unp = (struct sockaddr_un *) sa;

			/* OK to have no pathname bound to the socket: happens on
			   every connect() unless client calls bind() first. */
		if (unp->sun_path[0] == 0)
			strcpy(str, "(no pathname bound)");
		else
			snprintf(str, sizeof(str), "%s", unp->sun_path);
		return(str);
	}
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
	case AF_LINK: {
		struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;

		if (sdl->sdl_nlen > 0)
			snprintf(str, sizeof(str), "%*s",
					 sdl->sdl_nlen, &sdl->sdl_data[0]);
		else
			snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
		return(str);
	}
#endif
	default:
		snprintf(str, sizeof(str), "sock_ntop_host: unknown AF_xxx: %d, len %d",
				 sa->sa_family, salen);
		return(str);
	}
    return (NULL);
}

char* Sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    return sock_ntop_host(sa, salen);
}
