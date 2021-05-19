
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

#define STUDENTS 10

// Worker functions
void *ta_routine(void *);
void *student_routine(void *);

// Global variables
pthread_mutex_t mutex_h, mutex_w;
sem_t wakeup;
int helping = 0, waiting = 0;

int main(int argc, char *argv[])
{
    pthread_t ta, students[STUDENTS];

    // Initialize the mutex and the semaphore
    pthread_mutex_init(&mutex_h, NULL);
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
        int busy = 1;

        // Help the student
        pthread_mutex_lock(&mutex_h);
        helping = 1;
        pthread_mutex_unlock(&mutex_h);

        while (busy)
        {
            printf("TA is helping a student...\n");
            sleep(3);

            // Check if any other students need help
            pthread_mutex_lock(&mutex_w);
            if (waiting > 0)
                waiting--;
            else
                busy = 0;
            pthread_mutex_unlock(&mutex_w);
        }

        // Back to sleep
        pthread_mutex_lock(&mutex_h);
        helping = 0;
        pthread_mutex_unlock(&mutex_h);
    }
}

void *student_routine(void *unused)
{
    while (1)
    {
        // Check if the TA is asleep
        pthread_mutex_lock(&mutex_h);
        if (helping == 0)
        {
            // Wake TA up
            sem_post(&wakeup);
            pthread_mutex_unlock(&mutex_h);
            pthread_exit(0);
        }
        pthread_mutex_unlock(&mutex_h);

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
        sleep(5);
    }
}