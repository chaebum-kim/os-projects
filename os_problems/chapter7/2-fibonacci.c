/* 2-fibonacci.c
** A program that generates the Fibonacci sequence.
** Parent thread can access Fibonacci numbers as soon as they were
** computed by the child thread.
** Compiled with gcc -pthread 2-fibonacci.c -o fibonacci 
** Usage: ./fibonacci length
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// Global variable
int *nums;
int length;

// Worker fuction
void *fibonacci(void *params);

int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;
    sem_t *full;

    // Get user input
    length = atoi(argv[1]);

    // Allocate the memory
    nums = (int *)malloc(sizeof(int) * length);

    // Create the semaphore and initialize it to 0
    full = sem_open("FULL", O_CREAT, 0666, 0);

    // Set the default attributes of the thread
    pthread_attr_init(&attr);

    // Create the thread
    pthread_create(&tid, &attr, fibonacci, nums);

    // Print the result
    for (int i = 0; i < length; i++)
    {
        sem_wait(full);
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}

void *fibonacci(void *params)
{
    int *nums = (int *)params;
    int fib1 = -1;
    int fib2 = 1;
    sem_t *full = sem_open("FULL", O_CREAT, 0666, 0);

    for (int i = 0; i < length; i++)
    {
        nums[i] = fib1 + fib2;
        fib1 = fib2;
        fib2 = nums[i];
        sem_post(full);
    }

    pthread_exit(0);
}