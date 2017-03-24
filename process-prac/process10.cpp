#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <wait.h>
#include <iostream>
#include <iomanip>

const int mapped_size = 4096;
const int mapped_count = mapped_size / sizeof(int);

int main(int argc, char** argv)
{
    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    lseek(fd, mapped_size-1, SEEK_SET);
    write(fd, "", 1);
    lseek(fd, 0, SEEK_SET);
    int* base = (int*) mmap(0, mapped_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
    close(fd);

    pid_t pid = fork();
    if (pid == (pid_t)0) {
        for (int i = 0, *p = base; i < mapped_count; i++) {
            *p++ = i;
        }
        munmap(base, mapped_size);
    } else if (pid > (pid_t)0) {
        sleep(10);
        for (int i = 0, *p = base; i < mapped_count; i++, p++) {
            std::cout << std::setw(5) << *p << " ";
        }
        std::cout << std::endl;
        munmap(base, mapped_size);
    } else {
        return -1;
    }
}
