#include "./thread/unpthread.h"

static pthread_key_t rl_key;
static pthread_once_t rl_once = PTHREAD_ONCE_INIT;

static void readline_destructor(void* ptr)
{
    free(ptr);
}

static void readline_once(void)
{
    Pthread_key_create(&rl_key, readline_destructor);
}

using Rline = struct {
    int rl_cnt;
    char* rl_bufptr;
    char rl_buf[MAXLINE];
};

static ssize_t my_read(Rline* tsd, int fd, char* ptr)
{
    if (tsd->rl_cnt <= 0) {
again:
        if ((tsd->rl_cnt = read(fd, tsd->rl_buf, MAXLINE)) < 0) {
            if (errno == EINTR) {
                goto again;
            } else {
                return -1;
            }
        } else if (tsd->rl_cnt == 0) {
            return 0;
        }
        tsd->rl_bufptr = tsd->rl_buf;
    }
    --tsd->rl_cnt;
    *ptr = *tsd->rl_bufptr++;
    return 1;
}

ssize_t readline(int fd, void* vptr, size_t maxlen)
{
    Pthread_once(&rl_once, readline_once);

    Rline* tsd = NULL;
    if ((tsd = (Rline*) pthread_getspecific(rl_key)) == NULL) {
        tsd = (Rline *) Calloc (1, sizeof(Rline)); // init to 0.
        Pthread_setspecific(rl_key, tsd);
    }

    char* ptr = (char *) vptr;
    size_t rc, i;
    char c;
    for (i = 1; i < maxlen; ++i) {
        if ((rc = my_read(tsd, fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            *ptr = 0;
            return (i - 1);
        } else {
            return -1;
        }
    }
    *ptr = 0;
    return i;
}
