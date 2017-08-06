#include "unpthread.h"

#define MAXFILES 20
#define SERV "8000"

struct file {
    char* f_name;   // filename.
    char* f_host;   // hostname or IP address.
    int   f_fd;     // descriptor.
    int   f_flags;  // F_xxx below.
    pthread_t f_tid; // thread id.

} files[MAXFILES];

#define F_CONNECTING 1
#define F_READING    2
#define F_DONE       4
#define F_JOINED     8

#define GET_CMD "GET %s HTTP/1.0\r\n\r\n"

int nconn, nfiles, nlefttoconn, nlefttoread;

int ndone;
pthread_mutex_t ndone_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  ndone_cond = PTHREAD_COND_INITIALIZER;

void* do_get_read(void *);
void  home_page(const char*, const char*);
void  write_get_cmd(struct file *);

int main(int argc, char** argv)
{
    if (argc < 5) {
        err_quit("usage: ./web <#conns> <IPaddress> <homepage> file1 ...");
    }

    int maxconn = atoi(argv[1]);

    nfiles = min(argc-4, MAXFILES);

    int i;
    for (i = 0; i < nfiles; ++i) {
        files[i].f_name = argv[i+4];
        files[i].f_host = argv[2];
        files[i].f_flags = 0;
    }

    printf("nfiles = %d\n", nfiles);

    home_page(argv[2], argv[3]);

    nlefttoread = nlefttoconn = nfiles;
    nconn = 0;

    pthread_t tid;
    while (nlefttoread > 0) {
        while (nconn < maxconn && nlefttoconn > 0) {
            for (i = 0; i < nfiles; ++i) {
                if (files[i].f_flags == 0) {
                    break;
                }
            }
            if (i == nfiles) {
                err_quit("nlefttoconn = %d but nothing found", nlefttoconn);
            }

            files[i].f_flags = F_CONNECTING;
            Pthread_create(&tid, NULL, &do_get_read, &files[i]);
            files[i].f_tid = tid;
            ++nconn;
            --nlefttoconn;
        }

        Pthread_mutex_lock(&ndone_mutex);
        while (ndone == 0) {
            Pthread_cond_wait(&ndone_cond, &ndone_mutex);
        }

        struct file* fptr = NULL;
        for (i = 0; i < nfiles; ++i) {
            if (files[i].f_flags & F_DONE) {
                Pthread_join(files[i].f_tid, (void **) &fptr);
            }

            if (&files[i] != fptr) {
                err_quit("file[i] != fptr");
            }

            fptr->f_flags = F_JOINED; // clears F_DONE.
            --ndone;
            --nconn;
            --nlefttoread;
            printf("thread %ld for %s done\n", fptr->f_tid, fptr->f_name);
        }
        Pthread_mutex_unlock(&ndone_mutex);
    }

    exit(0);
}

void home_page(const char* host, const char* fname)
{
    int fd = Tcp_connect(host, SERV);

    char line[MAXLINE];
    int n = snprintf(line, sizeof(line), GET_CMD, fname);

    Write(fd, line, n);

    for ( ; ; ) {
        if ((n = Read(fd, line, MAXLINE)) == 0) {
            break; // server closed connection.
        }
        printf("read %d bytes of home page.\n", n);

        // do whatever with data.
        printf("data: %s\n", line);
    }
    printf("end-of-file on home page.\n");
    Close(fd);
}

void write_get_cmd(struct file* fptr)
{
    char line[MAXLINE];
    int n = snprintf(line, sizeof(line), GET_CMD, fptr->f_name);

    Write(fptr->f_fd, line, n);
    printf("wrote %d bytes for %s\n", n, fptr->f_name);
}

void* do_get_read(void* vptr)
{
    struct file* fptr = (struct file *) vptr;
    int fd = Tcp_connect(fptr->f_host, SERV);
    fptr->f_fd = fd;
    printf("do_get_read for %s, fd %d, thread %ld\n",
            fptr->f_name, fd, fptr->f_tid);

    write_get_cmd(fptr);

    char line[MAXLINE];
    int n;
    for ( ; ; ) {
        if ((n = Read(fd, line, MAXLINE)) == 0) {
            break;
        }
        printf("read %d bytes from %s\n", n, fptr->f_name);
    }

    printf("end-of-file on %s\n", fptr->f_name);
    Close(fd);

    Pthread_mutex_lock(&ndone_mutex);
    fptr->f_flags = F_DONE; // clears F_READING.
    ++ndone;
    Pthread_cond_signal(&ndone_cond);
    Pthread_mutex_unlock(&ndone_mutex);

    return fptr;
}
