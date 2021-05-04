/* 2-prime.c
** A multithreaded program that outputs prime numbers.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Global variables
int *prime_nums;
int count = 0;

// Worker function
void *get_primes(void *num);

// Helper function
_Bool is_prime(int num);

int main(int argc, char *argv[])
{
    int num;
    pthread_t tid;
    pthread_attr_t attr;

    // Get user input
    printf("Number: ");
    scanf("%d", &num);

    // Set the default attributes of the thread
    pthread_attr_init(&attr);

    // Create the thread
    pthread_create(&tid, &attr, get_primes, &num);

    // Wait for the thread to exit
    pthread_join(tid, NULL);

    // Print the result
    for (int i = 0; i < count; i++)
    {
        printf("%d ", prime_nums[i]);
    }
    printf("\n");

    free(prime_nums);

    return 0;
}

void *get_primes(void *num)
{
    int j = 0;
    int num_ = *(int *)num;

    // Allocate memory
    prime_nums = (int *)malloc(sizeof(int) * num_);

    for (int i = 1; i <= num_; i++)
    {
        if (is_prime(i))
        {
            prime_nums[j] = i;
            j++;
            count++;
        }
    }

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
