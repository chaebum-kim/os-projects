
#include <stdio.h>
#include <stdlib.h>
#include "pid_manager.h"

int main(int argc, char *argv[])
{
    int pid;

    // Allocate the map
    if (allocate_map() < 0)
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

    return 0;
}