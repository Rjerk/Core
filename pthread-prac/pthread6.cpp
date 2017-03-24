#include <pthread.h>
#include <cstdio>

static pthread_key_t tlk;

void writeToThreadLog(const char* msg)
{
    FILE* fp = (FILE*) pthread_getspecific (tlk);
    fprintf (fp, "%d: %s\n", (int) pthread_self(), msg);
}

void closeThreadLog(void* fp)
{
    fclose((FILE*)fp);
}

void* threadFunc(void* args)
{
    char filename[255];
    FILE* fp;
    sprintf (filename, "thread%d.log", (int)pthread_self());
    fp = fopen(filename, "w");
    pthread_setspecific(tlk, fp);
    writeToThreadLog("Thread starting...");
    return NULL;
}

int main()
{
    pthread_t thread[8];
    pthread_key_create(&tlk, closeThreadLog);
    for (int i = 0; i < 8; ++i) {
        pthread_create(&thread[i], NULL, threadFunc, NULL);
    }
    for (int i = 0; i < 8; ++i) {
        pthread_join(thread[i], NULL);
    }
    pthread_key_delete(tlk);
    return 0;
}
