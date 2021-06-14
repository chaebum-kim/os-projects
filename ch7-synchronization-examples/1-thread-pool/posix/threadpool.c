/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"
#include "queue.h"

#define NUMBER_OF_THREADS 3
#define TRUE 1

// this represents work that has to be
// completed by a thread in the pool
typedef struct _task
{
    void (*function)(void *p);
    void *data;
} task;

// the work queue
Queue work_queue;

// the worker bee
pthread_t bees[NUMBER_OF_THREADS];

// semaphore and mutex lock
sem_t sem;
pthread_mutex_t mutex;

// insert a task into the queue
// returns 0 if successful or 1 otherwise,
int enqueue(task t)
{
    if (queue_enqueue(&work_queue, &t, sizeof(task)) == NULL)
        return 1;

    return 0;
}

// remove a task from the queue
task dequeue()
{
    task temp;
    queue_dequeue(&work_queue, &temp, sizeof(task));
    return temp;
}

// the worker thread in the thread pool
void *worker(void *param)
{
    task worktodo;

    while (TRUE)
    {
        // Acquire the semaphore
        sem_wait(&sem);

        // Retrieve work from the queue
        pthread_mutex_lock(&mutex);
        worktodo = dequeue();
        pthread_mutex_unlock(&mutex);

        // execute the task
        execute(worktodo.function, worktodo.data);
    }
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*somefunction)(void *p), void *p)
{
    (*somefunction)(p);
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *p), void *p)
{
    task work;

    work.function = somefunction;
    work.data = p;

    // Add the task to the queue
    pthread_mutex_lock(&mutex);
    if (enqueue(work) != 0)
    {
        fprintf(stderr, "Pool Submisson Failed\n");
        pthread_mutex_unlock(&mutex);
        return 1;
    }
    pthread_mutex_unlock(&mutex);

    // Notify a wating thread that work is submitted
    sem_post(&sem);

    return 0;
}

// initialize the thread pool
void pool_init(void)
{
    // Create the queue
    queue_create(&work_queue);

    // Initialize the semaphore and the mutex lock
    sem_init(&sem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create the threads
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_create(&(bees[i]), NULL, worker, NULL);
}

// shutdown the thread pool
void pool_shutdown(void)
{
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_cancel(bees[i]);

    for (int i = 0; i < NUMBER_OF_THREADS; i++)
        pthread_join(bees[i], NULL);
}
