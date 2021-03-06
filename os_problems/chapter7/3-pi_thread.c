/* 3-pi.c
*  A program that calcuates pi using Monte Carlo technique.
*  This program utilizes several threads, each of which generates
*  random points, count the points within the circle, and update
*  the global count.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TOTAL 5000
#define THREADS 5

// Global variables
int count = 0;
pthread_mutex_t mutex;

// Worker function
void *monte_carlo(void *);

// Helper function
void generate_random_points(double points[][2]);
int count_incircle(double points[][2]);

int main(int argc, char *argv[])
{
    pthread_t tids[THREADS];

    // Create and initialize the mutex lock
    pthread_mutex_init(&mutex, NULL);

    // Create the threads
    for (int i = 0; i < THREADS; i++)
        pthread_create(&(tids[i]), NULL, monte_carlo, NULL);

    // Wait for the threads to exit
    for (int i = 0; i < THREADS; i++)
        pthread_join(tids[i], NULL);

    // Print the result
    printf("π = %f\n", 4 * count / (double)(TOTAL * THREADS));

    return 0;
}

void *monte_carlo(void *unused)
{
    double points[TOTAL][2];
    int mycount;

    // Generate random points
    generate_random_points(points);

    // Count the number of points within the circle
    mycount = count_incircle(points);

    // Update the global count
    pthread_mutex_lock(&mutex);
    count += mycount;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

void generate_random_points(double points[][2])
{
    double x, y;

    srand(time(NULL));

    for (int i = 0; i < TOTAL; i++)
    {
        // Generate random x point
        x = (double)rand() / RAND_MAX * 2 - 1;

        // Generate random y point
        y = (double)rand() / RAND_MAX * 2 - 1;

        // Save the coordinate in points
        points[i][0] = x;
        points[i][1] = y;
    }
}

int count_incircle(double points[][2])
{
    int count = 0;
    double x, y, r;

    for (int i = 0; i < TOTAL; i++)
    {
        x = points[i][0];
        y = points[i][1];
        r = sqrt(x * x + y * y);
        if (r <= 1.0)
            count++;
    }
    return count;
}