
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

// Worker function
void *routine(void *i);

// Helper function
void pickup_forks(int i);
void return_forks(int i);
void test(int i);

// Global variables
pthread_mutex_t mutex;
enum status
{
    eating,
    thinking,
    hungry
} state[5];
pthread_cond_t self[5];

int main(int argc, char *argv[])
{
    pthread_t tids[5];
    int nums[5] = {0, 1, 2, 3, 4};

    // Initialize the mutex and the condition variables
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 5; i++)
        pthread_cond_init(&(self[i]), NULL);

    // Create the threads
    for (int i = 0; i < 5; i++)
        pthread_create(&(tids[i]), NULL, routine, &(nums[i]));

    // Sleep for 10 seconds
    sleep(10);

    return 0;
}

void pickup_forks(int i)
{
    // Set state to hungry
    pthread_mutex_lock(&mutex);
    state[i] = hungry;

    // Pick up the forks and eat if both forks are available
    test(i);
    if (state[i] != eating)
        pthread_cond_wait(&(self[i]), &mutex);

    pthread_mutex_unlock(&mutex);
}

void return_forks(int i)
{
    // Set state to thinking
    pthread_mutex_lock(&mutex);
    state[i] = thinking;

    // Check if others are waiting for the forks
    test((i + 4) % 5);
    test((i + 1) % 5);

    pthread_mutex_unlock(&mutex);
}

void test(int i)
{
    if ((state[(i + 4) % 5] != eating) && (state[i] == hungry) && (state[(i + 1) % 5] != eating))
    {
        state[i] = eating;
        pthread_cond_signal(&(self[i]));
    }
}

void *routine(void *i)
{
    while (1)
    {
        int num = *((int *)i);
        pickup_forks(num);
        printf("Philosopher%d is eating.\n", num);
        sleep(3);
        return_forks(num);
        printf("Philosopher%d is thinking.\n", num);
        sleep(3);
    }
}