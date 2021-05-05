/* 4-pi_openmp.c
** A program that calcuates pi using Monte Carlo technique.
** This program utilizes OpenMp to parallelize the generation of points.
** Compiled with gcc -fopenmp 4-pi_openmp.c -o pi2 -lm
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define TOTAL 10000

// Helper function
int count_incircle(double points[][2]);

int main(int argc, char *argv[])
{
    double points[TOTAL][2];
    int i, count;

    srand(time(NULL));

    omp_set_num_threads(2);

// Generate random points
#pragma omp parallel for
    for (i = 0; i < TOTAL; i++)
    {
        double x, y;
        // Generate random x point
        x = (double)rand() / RAND_MAX * 2 - 1;

        // Generate random y point
        y = (double)rand() / RAND_MAX * 2 - 1;

        // Save the coordinate in points
        points[i][0] = x;
        points[i][1] = y;
    }

    // Count the number of points within the circle
    count = count_incircle(points);

    // Print the result
    printf("π = %f\n", 4 * count / (double)TOTAL);

    return 0;
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