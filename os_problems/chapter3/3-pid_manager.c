/* 3-pid_manager.c
** It is an API for obtaining and releasing a pid.
*/

#include <stdlib.h>
#include <stdio.h>

#define MIN_PID 300
#define MAX_PID 5000
#define LENGTH 4701

// Function prototypes
int allocate_map();
int allocate_pid();
void release_pid(int pid);

// Pointer to a pids map
int *map;

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

// Test
int main(int argc, char *argv[])
{
    int m, pid;
    m = allocate_map();

    // Allocate the map
    if (m < 0)
    {
        fprintf(stderr, "Failed to allocate the map.");
        return 1;
    }

    // Allocate pid
    pid = allocate_pid();
    if (pid < 0)
    {
        fprintf(stderr, "Failed to allocate pid.");
        return 1;
    }
    printf("pid is %d\n", pid);

    // Release pid
    release_pid(pid);

    // Free map
    free(map);

    return 0;
}
