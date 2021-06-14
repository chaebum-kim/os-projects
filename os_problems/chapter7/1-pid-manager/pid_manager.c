/* pid_manager.c
*  Modified programming problem 4.28 by ensuring that the data structure
*  used to represent the availability of process identifiers is safe
*  from race conditions. Mutex locks are used.
*/

#include <stdio.h>
#include "pid_manager.h"

/* Create and initialize a data structure for representing pids.
   Return -1 if unsuccessful, 1 if succesful. */
int allocate_map()
{
    // Initialize the data structure
    for (int i = 0; i < LENGTH; i++)
    {
        map[i] = 0;
    }

    // Create and initialize the mutex lock
    pthread_mutex_init(&mutex, NULL);

    return map > 0 ? 1 : -1;
}

/* Allocate and returns a pid. Return -1 if unable to allocate 
   a pid(all pids are in use) */
int allocate_pid()
{
    // Acquire the mutex lock
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < LENGTH; i++)
    {
        if (map[i] == 0)
        {
            map[i] = 1;
            pthread_mutex_unlock(&mutex);
            return i + MIN_PID;
        }
    }
    pthread_mutex_unlock(&mutex);
    return -1;
}

/* Release a pid */
void release_pid(int pid)
{
    map[pid - MIN_PID] = 0;
}
