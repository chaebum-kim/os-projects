/* pid_manager.c
** It is an API for obtaining and releasing a pid.
*/

#include <stdlib.h>
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
