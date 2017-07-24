#include "../apue.h"

int main()
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        err_sys("lseek error");
    } else {
        printf ("seek ok.\n");
    }
    exit(0);
}
