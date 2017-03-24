#include <iostream>
#include <pthread.h>
#include <list>

struct Job {
    Job(int _x = 0, int _y = 0): x(_x), y(_y) { }
    int x;
    int y;
};

std::list<Job*> job_queue;

pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void processJob(Job* job)
{
    std::cout << "Thread " << (int) pthread_self()
        << " processing (" << job->x << ", " << job->y << ")" << std::endl;
}

void* dequeueJob(void* arg)
{
    while (true) {
        Job* job = NULL;

        pthread_mutex_lock(&job_queue_mutex);

        if (!job_queue.empty()) {
            job = job_queue.front();
            job_queue.pop_front();
        }

        pthread_mutex_unlock(&job_queue_mutex);
        if (!job) {
            break;
        }

        processJob(job);
        delete job;
        job = NULL;

    }
    return NULL;
}

void* enqueueJob(void* arg)
{
    Job* job = reinterpret_cast<Job*>(arg);

    pthread_mutex_lock(&job_queue_mutex);

    job_queue.push_back(job);

    std::cout << "Thread " << (int)pthread_self()
        << " enqueueing (" << job->x << ", " << job->y << ")" << std::endl;

    pthread_mutex_unlock(&job_queue_mutex);
    return NULL;
}

int main()
{
    pthread_t threads[8];
    for (int i = 0; i < 5; ++i) {
        Job* job = new Job(i+1, (i+1)*2);
        pthread_create(&threads[i], NULL, enqueueJob, job);
    }

    for (int i = 5; i < 8; ++i) {
        pthread_create(&threads[i], NULL, dequeueJob, NULL);
    }

    for (int i = 0; i < 8; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
