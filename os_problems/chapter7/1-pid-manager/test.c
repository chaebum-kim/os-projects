

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "pid_manager.h"

#define TEST 100

// Worker function
void *test(void *);

int main(int argc, char *argv[])
{
    pthread_t tids[TEST];

    // Allocate map
    if (allocate_map() == -1)
    {
        fprintf(stderr, "Allocation Failed.\n");
        return 1;
    }

    // Create the threads
    for (int i = 0; i < TEST; i++)
        pthread_create(&(tids[i]), NULL, test, NULL);

    // Wait for the threads to exit
    for (int i = 0; i < TEST; i++)
        pthread_join(tids[i], NULL);

    return 0;
}

void *test(void *unused)
{
    int pid;

    // Allocate pid
    pid = allocate_pid();

    if (pid == -1)
    {
        printf("Request For PID Failed.\n");
        pthread_exit(0);
    }

    printf("My pid is %d\n", pid);
    sleep(3);

    // Release pid
    release_pid(pid);

    pthread_exit(0);
}