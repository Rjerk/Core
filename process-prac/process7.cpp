#include <cstdlib>
#include <cstdio>
#include <unistd.h>

const int bufsize = 28;

void Write(const char* msg, int count, FILE* stream)
{
    for (; count > 0; --count) {
        fprintf (stream, "%s\n", msg);
        fflush(stream);
        sleep(1);
    }
}

void Read(FILE* stream)
{
    char buf[bufsize];
    while (!feof(stream) && !ferror(stream)
            && fgets(buf, sizeof(buf), stream) != NULL) {
        fprintf (stdout, "Data received: \n");
        fputs (buf, stdout);
    }
}

int main()
{
    int fds[2];
    pipe(fds);
    pid_t pid = fork();
    if (pid == 0) {
        close(fds[1]); // close pipe write-end
        FILE* stream = fdopen(fds[0], "r"); // transfer fd to FILE*
        Read(stream);
        close(fds[0]);
    } else if (pid > 0) {
        char buf[bufsize];
        for (int i = 0; i < bufsize-2; ++i) {
            buf[i] = 'A' + i % 26;
        }
        buf[bufsize-1] = buf[bufsize-2] = '\0';
        close(fds[0]); // write-only, close pip read-end
        FILE* stream = fdopen(fds[1], "w");
        Write(buf, 3, stream);
        close(fds[1]);
    } else {
        return -1;
    }
}
