/* 1-bridge.c
* Solution to Exercise 8.30 using posix synchronization
*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define FARMERS 5

// Worker function
void *farmer(void *param);

// Global variables
pthread_mutex_t bridge;

int main(int argc, char *argv[])
{
    pthread_t northbound[FARMERS], southbound[FARMERS];

    // Create and initialize the mutex lock
    pthread_mutex_init(&bridge, NULL);

    // Create threads
    for (int i = 0; i < FARMERS; i++)
    {
        pthread_create(&(northbound[i]), NULL, farmer, "north");
        pthread_create(&(southbound[i]), NULL, farmer, "south");
    }

    // Wait for the threads to exit
    for (int i = 0; i < FARMERS; i++)
    {
        pthread_join(northbound[i], NULL);
        pthread_join(southbound[i], NULL);
    }

    return 0;
}

void *farmer(void *param)
{
    // Acquire the mutex lock
    pthread_mutex_lock(&bridge);

    // Cross the bridge
    if (strcmp((char *)param, "north") == 0)
        printf("A northbound farmer is crossing the bridge.\n");
    else
        printf("A southbound farmer is crossing the bridge.\n");

    sleep(1);

    // Release the mutex lock
    pthread_mutex_unlock(&bridge);

    pthread_exit(0);
}