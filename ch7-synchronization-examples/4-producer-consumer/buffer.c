#include <pthread.h>
#include <semaphore.h>
#include <memory.h>
#include "buffer.h"

// The buffer
buffer_item buffer[BUFFER_SIZE];

// Buffer manipulation variables
int produce = 0, consume = 0;

// Mutex and semaphores
pthread_mutex_t mutex;
sem_t empty, full;

void init_buffer(void)
{
    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
}

int insert_item(buffer_item item)
{
    // Wait if the buffer is full
    if (sem_wait(&empty) < 0)
        return -1;

    // Insert item
    if (pthread_mutex_lock(&mutex))
        return -1;
    buffer[produce] = item;
    produce = (produce + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);

    // Notify that I produced one item
    sem_post(&full);

    return 0;
}

int remove_item(buffer_item *item)
{
    // Wait if the buffer is empty
    if (sem_wait(&full) < 0)
        return -1;

    // Remove an object from buffer placing it in item
    if (pthread_mutex_lock(&mutex))
        return -1;
    memcpy(item, &(buffer[consume]), sizeof(buffer_item));
    consume = (consume + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&mutex);

    // Notify that I consumed one item
    sem_post(&empty);

    return 0;
}
