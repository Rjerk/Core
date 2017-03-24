#include <cstdio>
#include <sys/shm.h>
#include <sys/stat.h>

int main()
{
    struct shmid_ds shmbuf;
    int seg_size;
    const int shared_size = 0x6400;

    int seg_id = shmget(IPC_PRIVATE, shared_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    char* shared_mem = (char*) shmat(seg_id, 0, 0);
    printf ("Shared memory attched at %p\n", shared_mem);

    shmctl(seg_id, IPC_STAT, &shmbuf);
    seg_size = shmbuf.shm_segsz;
    printf ("Segment size: %d\n", seg_size);

    sprintf (shared_mem, "Hello, world.");

    shmdt(shared_mem);

    shared_mem = (char*) shmat (seg_id, (void*) 0x5000000, 0);
    printf ("Shared memory reattached at %p\n", shared_mem);

    printf ("%s\n", shared_mem);

    shmdt(shared_mem);
    shmctl(seg_id, IPC_RMID, 0);
    return 0;
}
