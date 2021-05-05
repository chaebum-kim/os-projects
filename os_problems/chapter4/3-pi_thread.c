/* 3-pi_thread.c
** A program that calcuates pi using Monte Carlo technique.
** This program utilizes a thread to generate a number of random points
** and count the number of points that occur within the circle.
** Compiled with gcc -pthread 3-pi_thread.c -o pi -lm.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TOTAL 10000

// Global variables
int count = 0;

// Worker function
void *monte_carlo(void *);

// Helper function
void generate_random_points(double points[][2]);
int count_incircle(double points[][2]);

int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;

    // Set the default attributes of the thread
    pthread_attr_init(&attr);

    // Create the thread
    pthread_create(&tid, &attr, monte_carlo, NULL);

    // Wait for the thread to exit
    pthread_join(tid, NULL);

    // Print the result
    printf("π = %f\n", 4 * count / (double)TOTAL);

    return 0;
}

void *monte_carlo(void *unused)
{
    double points[TOTAL][2];

    // Generate random points
    generate_random_points(points);

    // Count the number of points within the circle
    count = count_incircle(points);

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