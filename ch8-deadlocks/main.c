/* main.c
** A prgram that tests banker's algorithm.
*/

#include "banker.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 16
#define MAX_COMMAND 4

int parse(char *input, char *command, int *arguments);
void request(int *arguments);
void release(int *arguments);
void output_values(void);

int main(int argc, char *argv[])
{
    char input[MAX_LINE];
    char command[MAX_COMMAND];
    int arguments[NUMBER_OF_RESOURCES + 1] = {
        0,
    };

    // Get command line arguments and initialize availabe resources
    init_available(argc, argv);

    // Initilize maximum resources
    init_maximum("maximum.txt");

    // Initialize need
    init_need();

    while (1)
    {
        // Wait for the user to enter a command
        fgets(input, MAX_LINE, stdin);

        // Parse the command
        if (parse(input, command, arguments) < 0)
        {
            printf("Command Not Found.\n");
            continue;
        }

        // Execute the command
        if (strcmp(command, "RQ") == 0)
            request(arguments);
        else if (strcmp(command, "RL") == 0)
            release(arguments);
        else if (strcmp(command, "*") == 0)
            output_values();
        else
            return 0;

        // Initialize command and arguments
        memset(command, 0, MAX_COMMAND);
        memset(arguments, 0, sizeof(int) * (NUMBER_OF_RESOURCES + 1));
    }

    return 0;
}

int parse(char *input, char *command, int *arguments)
{
    char *temp[NUMBER_OF_RESOURCES + 2];
    int i = 0;

    temp[i] = strtok(input, " \n");
    while (temp[i] != NULL)
    {
        i++;
        temp[i] = strtok(NULL, " \n");
    }

    if (strcmp(temp[0], "RQ") != 0 && strcmp(temp[0], "RL") != 0 &&
        strcmp(temp[0], "*") != 0 && strcmp(temp[0], "exit") != 0)
        return -1;

    memcpy(command, temp[0], MAX_COMMAND);
    int j = 1;
    while (j < NUMBER_OF_RESOURCES + 2 && temp[j] != NULL)
    {
        arguments[j - 1] = atoi(temp[j]);
        j++;
    }

    return 0;
}

void request(int *arguments)
{
    if (request_resources(arguments[0], arguments + 1) < 0)
        printf("Resource Request Denied.\n");
    else
        printf("Resource Request Granted.\n");
}

void release(int *arguments)
{
    release_resources(arguments[0], arguments + 1);
    printf("Resource Released.\n");
}

void output_values(void)
{
    // Print out available resources
    printf("Available Resources\n");
    printf("=====================================\n");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        printf("%d ", available[i]);
    printf("\n");

    printf("\n");

    // Print out maximum resources
    printf("Maximum Resources\n");
    printf("=====================================\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        printf("customer%d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
            printf("%d ", maximum[i][j]);
        printf("\n");
    }

    printf("\n");

    // Print out allocated resources
    printf("Allocated Resources\n");
    printf("=====================================\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        printf("customer%d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }

    printf("\n");

    // Print out needed resources
    printf("Needed Resources\n");
    printf("=====================================\n");
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        printf("customer%d: ", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}