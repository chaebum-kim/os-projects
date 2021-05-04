/* 1-static.c
** A multithreaded program that calcuates the average, the maximum,
** the minimun values or numbers respectively.
** Compiled and linked with gcc -pthread 1-static.c -o static
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables
int average;
int maximum;
int minimum;
int length;

// Workers
void *avg(int *nums);
void *max(int *nums);
void *min(int *nums);

/* main */
int main(int argc, char *argv[])
{
    pthread_t tids[3];
    pthread_attr_t attrs[3];
    void *p[3] = {avg, max, min};
    int *nums;

    // Save user inputs into array of numbers
    length = argc - 1;
    nums = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
    {
        nums[i] = atoi(argv[i + 1]);
    }

    for (int i = 0; i < 3; i++)
    {
        // Set the default attributes of the threads
        pthread_attr_init(&(attrs[i]));

        // Create the thread
        pthread_create(&(tids[i]), &(attrs[i]), p[i], nums);
    }

    // Wait for the thread to exit
    for (int i = 0; i < 3; i++)
    {
        pthread_join(tids[i], NULL);
    }

    // Print the results
    printf("The average value is %d\n", average);
    printf("The minimum value is %d\n", minimum);
    printf("The maximum value is %d\n", maximum);

    free(nums);

    return 0;
}

void *avg(int *nums)
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += nums[i];
    }

    average = sum / length;

    pthread_exit(0);
}

void *max(int *nums)
{
    maximum = 0;
    for (int i = 0; i < length; i++)
    {
        if (nums[i] > maximum)
            maximum = nums[i];
    }

    pthread_exit(0);
}

void *min(int *nums)
{
    minimum = nums[0];

    for (int i = 1; i < length; i++)
    {
        if (nums[i] < minimum)
            minimum = nums[i];
    }

    pthread_exit(0);
}
