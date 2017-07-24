#include "../apue.h"

int main(int, char* argv[])
{
    fprintf (stderr, "EACCES: %s\n", strerror(EACCES));
    errno  = ENOENT;
    perror(argv[0]);
    exit(0);
}
