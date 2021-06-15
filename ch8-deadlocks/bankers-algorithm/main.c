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

int parse_input(char *input, char *args[]);
int request(int argc, char *args[]);
int release(int argc, char *args[]);
void output_values(void);

int main(int argc, char *argv[])
{
    char input[MAX_LINE], *args[MAX_LINE];

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
        int n = parse_input(input, args);

        // Execute the command
        if (strcmp(args[0], "RQ") == 0)
            request(n - 1, args + 1);
        else if (strcmp(args[0], "RL") == 0)
            release(n - 1, args + 1);
        else if (strcmp(args[0], "*") == 0)
            output_values();
        else if (strcmp(args[0], "exit") == 0)
            break;
        else
            printf("Error: Unrecognized command\n");

        // Initialize command and arguments
        memset(input, 0, MAX_LINE);
        memset(args, 0, sizeof(args));
    }

    return 0;
}

int parse_input(char *input, char *args[])
{
    int i = 0;

    args[i] = strtok(input, " \n");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " \n");
    }

    return i;
}

int request(int argc, char *args[])
{
    int customer_num, resources[NUMBER_OF_RESOURCES];

    if (argc != 5)
    {
        printf("Usage: RQ <customer_num> <# of resources>\n");
        return -1;
    }

    customer_num = atoi(args[0]);

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        resources[i] = atoi(args[i + 1]);

    if (request_resources(customer_num, resources) < 0)
        printf("Resource Request Denied.\n");
    else
        printf("Resource Request Granted.\n");

    return 0;
}

int release(int argc, char *args[])
{
    int customer_num, resources[NUMBER_OF_RESOURCES];

    if (argc != 5)
    {
        printf("Usage: RL customer_num resources\n");
        return -1;
    }

    customer_num = atoi(args[0]);

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        resources[i] = atoi(args[i + 1]);

    release_resources(customer_num, resources);
    printf("Resource Released.\n");

    return 0;
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