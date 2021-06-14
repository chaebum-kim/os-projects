
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define STUDENTS 10

// Worker functions
void *ta_routine(void *);
void *student_routine(void *);

// Global variables
pthread_mutex_t mutex_s, mutex_w;
sem_t wakeup;
int sleeping = 1, waiting = 0;

int main(int argc, char *argv[])
{
    pthread_t ta, students[STUDENTS];

    // Initialize the mutex and the semaphore
    pthread_mutex_init(&mutex_s, NULL);
    pthread_mutex_init(&mutex_w, NULL);
    sem_init(&wakeup, 0, 0);

    // Create the threads
    pthread_create(&ta, NULL, ta_routine, NULL);
    for (int i = 0; i < STUDENTS; i++)
        pthread_create(&(students[i]), NULL, student_routine, NULL);

    // Wait for the threads to exit
    for (int i = 0; i < STUDENTS; i++)
        pthread_join(students[i], NULL);
    pthread_join(ta, NULL);

    return 0;
}

void *ta_routine(void *unused)
{
    while (1)
    {
        // Wait for the students to wake me up
        printf("TA is sleeping...\n");
        sem_wait(&wakeup);

        // Wake up
        pthread_mutex_lock(&mutex_s);
        sleeping = 0;
        pthread_mutex_unlock(&mutex_s);

        while (1)
        {
            printf("TA is helping a student...\n");
            sleep(1);

            // Check if any other students need help
            pthread_mutex_lock(&mutex_w);
            if (waiting > 0)
                waiting--;
            else
            {
                pthread_mutex_unlock(&mutex_w);
                break;
            }
            pthread_mutex_unlock(&mutex_w);
        }

        // Back to sleep
        pthread_mutex_lock(&mutex_s);
        sleeping = 1;
        pthread_mutex_unlock(&mutex_s);
    }
}

void *student_routine(void *unused)
{
    while (1)
    {
        // Check if the TA is asleep
        pthread_mutex_lock(&mutex_s);
        if (sleeping)
        {
            // Wake TA up
            sem_post(&wakeup);
            pthread_mutex_unlock(&mutex_s);
            pthread_exit(0);
        }
        pthread_mutex_unlock(&mutex_s);

        // Check if the seats are available
        pthread_mutex_lock(&mutex_w);
        if (waiting < 3)
        {
            waiting++;
            pthread_mutex_unlock(&mutex_w);
            pthread_exit(0);
        }
        pthread_mutex_unlock(&mutex_w);

        // Come back later
        printf("A student will come back later...\n");
        sleep(2);
    }
}