/* 6-fibonacci.c
*  A program that generates the Fibonacci sequence
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable
int *nums;
int length;

// Worker fuction
void *fibonacci(void *params);

int main(int argc, char *argv[])
{
    pthread_t tid;

    // Get the command line arguments
    length = atoi(argv[1]);

    // Allocate the memory
    nums = (int *)malloc(sizeof(int) * length);

    // Create the thread
    pthread_create(&tid, NULL, fibonacci, nums);

    // Wait for the thread to exit
    pthread_join(tid, NULL);

    // Print the result
    for (int i = 0; i < length; i++)
        printf("%d ", nums[i]);
    printf("\n");

    free(nums);

    return 0;
}

void *fibonacci(void *params)
{
    int *nums = (int *)params;
    int fib1 = -1;
    int fib2 = 1;

    for (int i = 0; i < length; i++)
    {
        nums[i] = fib1 + fib2;
        fib1 = fib2;
        fib2 = nums[i];
    }

    pthread_exit(0);
}