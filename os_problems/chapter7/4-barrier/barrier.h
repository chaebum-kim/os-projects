#ifndef BARRIER
#define BARRIER

#include <pthread.h>

int threads;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

int init(int n);
int barrier_point(void);

#endif