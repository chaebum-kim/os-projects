/* 5-collatz_shm.c
** A program that generates collatz sequence given a positive number
** using shared memory.
*/

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function prototype
int collatz(int num);
int validate(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    const char *name = "SEQUENCE"; // Name of the shared memory object
    const int SIZE = 8192;         // The size (in bytes) of shared memory object

    char *ptr; // Pointer to shared memory object
    int fd;    // Shared memory file descriptor
    int num, count;

    pid_t pid;

    // Validate user input
    num = validate(argc, argv);

    // Create shared memory object
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    // Configure the size of the shared memory object
    ftruncate(fd, SIZE);

    // Memory map the shared memory object
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Fork a child process
    pid = fork();

    if (pid < 0)
        fprintf(stderr, "Fork Failed");

    if (pid == 0) // Child process
    {
        count = 0;
        char *p = ptr;

        ptr += sizeof(int); // Leave space for the count variable

        while (num != 1)
        {
            // Write the number to the shared memory object
            memcpy(ptr, &num, sizeof(int));
            count += 1;
            ptr += sizeof(int);
            num = collatz(num);
        }
        memcpy(ptr, &num, sizeof(int));
        ptr += sizeof(int);
        count += 1;

        // Write the count to the shared memory object
        memcpy(p, &count, sizeof(int));
    }
    else // Parent process
    {
        wait(NULL);

        // Read from the shared memory object

        // Read count
        memcpy(&count, ptr, sizeof(int));
        ptr += sizeof(int);

        // Read numbers
        for (int i = 0; i < count - 1; i++)
        {
            printf("%d, ", ((int *)ptr)[i]);
        }
        printf("%d\n", ((int *)ptr)[count - 1]);

        // Remove the shared memory object
        shm_unlink(name);
    }

    return 0;
}

/* Generate the next collatz number */
int collatz(int num)
{
    if (num % 2 == 0)
        return num / 2;
    else
        return 3 * num + 1;
}

/* Validate the user input */
int validate(int argc, char *argv[])
{
    int num;

    // Check if the number of inputs is 1
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./collatz poistivie_integer\n");
        exit(1);
    }

    // Check if the input is number
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            fprintf(stderr, "usage: ./collatz poistivie_integer\n");
            exit(1);
        }
    }

    // Check if the input is positive number
    num = atoi(argv[1]);
    if (num <= 0)
    {
        fprintf(stderr, "usage: ./collatz poistivie_integer\n");
        exit(1);
    }

    return num;
}