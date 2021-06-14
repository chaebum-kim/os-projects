/* 2-prime.c
*  A multithreaded program that outputs prime numbers.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Worker function
void *output_primes(void *num);

// Helper function
_Bool is_prime(int num);

int main(int argc, char *argv[])
{
    int num;
    pthread_t tid;

    // Get user input
    printf("Number: ");
    scanf("%d", &num);

    // Create the thread
    pthread_create(&tid, NULL, output_primes, &num);

    // Wait for the thread to exit
    pthread_join(tid, NULL);

    return 0;
}

void *output_primes(void *num)
{
    int num_ = *(int *)num;

    for (int i = 1; i <= num_; i++)
    {
        if (is_prime(i))
            printf("%d ", i);
    }
    printf("\n");

    pthread_exit(0);
}

_Bool is_prime(int num)
{
    if (num <= 2)
        return false;

    for (int div = 2; div < num; div++)
    {
        if (num % div == 0)
            return false;
    }
    return true;
}
