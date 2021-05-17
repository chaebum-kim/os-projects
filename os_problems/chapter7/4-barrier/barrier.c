/* barrier.c
** A barrier API for synchronizing the activity of a number of threads.
*/

#include "barrier.h"
#include <pthread.h>

int threads;
pthread_mutex_t mutex;
pthread_cond_t cond_var;

int init(int n)
{
    threads = n;

    if (pthread_mutex_init(&mutex, NULL) != 0)
        return -1;
    if (pthread_cond_init(&cond_var, NULL) != 0)
        return -1;

    return 0;
}

int barrier_point(void)
{
    pthread_mutex_lock(&mutex);
    threads -= 1;
    while (threads > 0)
        pthread_cond_wait(&cond_var, &mutex);
    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mutex);

    return 0;
}