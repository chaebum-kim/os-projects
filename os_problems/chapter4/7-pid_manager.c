/* 7-pid_manager.c
** Modify programming problem 3.20(pid manager). The modification includes
** multithreaded program that tests pid manager.
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MIN_PID 300
#define MAX_PID 5000
#define LENGTH 4701
#define TEST 100

// Function prototypes for API
int allocate_map();
int allocate_pid();
void release_pid(int pid);

// Worker function
void *test(void *);

// Pointer to a pids map
int *map;

// Test
int main(int argc, char *argv[])
{
    pthread_t tids[TEST];
    pthread_attr_t attrs[TEST];

    // Allocate map
    if (allocate_map() == -1)
    {
        fprintf(stderr, "Allocation Failed.\n");
        return 1;
    }

    for (int i = 0; i < TEST; i++)
    {
        // Set the default attributes of the thread
        pthread_attr_init(&(attrs[i]));

        // Create the thread
        pthread_create(&(tids[i]), &(attrs[i]), test, NULL);
    }

    // Wait for the threads to exit
    for (int i = 0; i < TEST; i++)
    {
        pthread_join(tids[i], NULL);
    }

    printf("Done\n");

    // Free map
    free(map);

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

/******************** pid manager API *************************/
/* Create and initialize a data structure for representing pids.
   Return -1 if unsuccessful, 1 if succesful. */
int allocate_map()
{
    // Create a data structure representing pids
    map = (int *)malloc(LENGTH * sizeof(int));

    // Initialize the data structure
    for (int i = 0; i < LENGTH; i++)
    {
        map[i] = 0;
    }

    return map > 0 ? 1 : -1;
}

/* Allocate and returns a pid. Return -1 if unable to allocate 
   a pid(all pids are in use) */
int allocate_pid()
{
    for (int i = 0; i < LENGTH; i++)
    {
        if (map[i] == 0)
        {
            map[i] = 1;
            return i + MIN_PID;
        }
    }
    return -1;
}

/* Release a pid */
void release_pid(int pid)
{
    map[pid - MIN_PID] = 0;
}
