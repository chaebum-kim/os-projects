
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "barrier.h"

#define THREADS 3

// Worker function
void *worker(void *);

int main(int argc, char *argv[])
{
    pthread_t tids[THREADS];

    // Initialize the barrier
    init(THREADS);

    // Create the threads
    for (int i = 0; i < THREADS; i++)
        pthread_create(&(tids[i]), NULL, worker, NULL);

    // Wait for threads to exit
    for (int i = 0; i < THREADS; i++)
        pthread_join(tids[i], NULL);

    return 0;
}

void *worker(void *unused)
{
    printf("Sleeping\n");
    barrier_point();
    printf("Awake\n");

    pthread_exit(0);
}
