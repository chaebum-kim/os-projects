/* test.c
*  Modified the programming problem 3.20(pid manager).
*  A multithreaded program that tests pid manager.
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pid_manager.h"

#define NUMBER_OF_THREADS 100

// Worker function
void *test(void *);

int main(int argc, char *argv[])
{
    pthread_t tids[NUMBER_OF_THREADS];

    // Allocate map
    if (allocate_map() == -1)
    {
        fprintf(stderr, "Allocation Failed.\n");
        return 1;
    }

    // Create the thread
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_create(&(tids[i]), NULL, test, NULL);

    // Wait for the threads to exit
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(tids[i], NULL);

    printf("Done\n");

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
