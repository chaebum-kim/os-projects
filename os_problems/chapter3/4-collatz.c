/* collatz.c
** A program that generates collatz sequence given a positive number.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function prototype
int collatz(int num);
int validate(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    pid_t pid;
    int num;

    // Validate user input
    num = validate(argc, argv);

    // Fork a child process
    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed.");
    }

    if (pid == 0) // Child process
    {
        while (num != 1)
        {
            printf("%d, ", num);
            num = collatz(num);
        }
        printf("%d\n", num);
    }
    else
    {
        wait(NULL);
    }

    return 0;
}

/* Generate the next collatz number */
int collatz(int num)
{
    if (num % 2 == 0)
    {
        return num / 2;
    }
    else
    {
        return 3 * num + 1;
    }
}

/* Validate the user input */
int validate(int argc, char *argv[])
{
    int length, num;

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