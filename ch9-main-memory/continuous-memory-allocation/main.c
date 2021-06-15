/* main.c
*  A program that simulates continuous memory allocation.
*/

#include "cma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX_LINE 128

int parse_input(char *input, char *args[]);
int request(int argc, char *args[]);
int release(int argc, char *args[]);

int main(int argc, char *argv[])
{
    char input[MAX_LINE], *args[MAX_LINE];
    int n;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./allocator <amount of memory>\n");
        return 1;
    }

    // Initialize the memory
    init_memory(strtoul(argv[1], NULL, 0));

    while (1)
    {
        memset(input, 0, MAX_LINE);
        memset(args, 0, sizeof(args));
        fflush(stdout);
        printf("allocator> ");

        fgets(input, MAX_LINE, stdin);

        n = parse_input(input, args);

        if (strcasecmp(args[0], "RQ") == 0)
            request(n - 1, args + 1);
        else if (strcasecmp(args[0], "RL") == 0)
            release(n - 1, args + 1);
        else if (strcasecmp(args[0], "STAT") == 0)
            report();
        else if (strcasecmp(args[0], "C") == 0)
            compact();
        else if (strcasecmp(args[0], "X") == 0)
            break;
        else
            printf("Error: Unrecognized command\n");
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
    ulong size;
    Flag flag;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: RQ <name> <size> <flag>\n");
        return -1;
    }

    size = strtoul(args[1], NULL, 0);

    if (strcasecmp(args[2], "F") == 0)
        flag = F;
    else if (strcasecmp(args[2], "B") == 0)
        flag = B;
    else if (strcasecmp(args[2], "W") == 0)
        flag = W;
    else
    {
        fprintf(stderr, "Error: Unrecognized flag %s", args[2]);
        return -1;
    }

    if (request_memory(args[0], size, flag) < 0)
    {
        fprintf(stderr, "Failed: Not enough memory\n");
        return -1;
    }

    return 0;
}

int release(int argc, char *args[])
{
    if (argc != 1)
    {
        fprintf(stderr, "Usage: RL <name>\n");
        return -1;
    }

    release_memory(args[0]);

    return 0;
}