
#ifndef PID_MANAGER_H
#define PID_MANAGER_H

#include <pthread.h>

#define MIN_PID 300
#define MAX_PID 5000
#define LENGTH 4701

// Function prototypes
int allocate_map();
int allocate_pid();
void release_pid(int pid);

// Pointer to a pids map
int map[LENGTH];

// Mutex lock
pthread_mutex_t mutex;

#endif