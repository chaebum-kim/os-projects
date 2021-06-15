
#include "banker.h"
#include <stdlib.h>
#include <memory.h>

void init_available(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: ./main <# of resources>\n");
        exit(1);
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        available[i] = atoi(argv[i + 1]);
}

void init_maximum(char *filename)
{
    FILE *file = NULL;

    if ((file = fopen(filename, "r")) == NULL)
        exit(1);

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
            fscanf(file, "%d%*c", &(maximum[i][j]));
    }

    fclose(file);
}

void init_need(void)
{
    memcpy(need, maximum, sizeof(maximum));
}

int request_resources(int customer_num, int request[])
{
    if (compare_array(request, need[customer_num], NUMBER_OF_RESOURCES) > 0)
        return -1;
    if (compare_array(request, available, NUMBER_OF_RESOURCES) > 0)
        return -1;

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }

    if (is_safe() < 0)
    {
        // Roll back
        release_resources(customer_num, request);
        return -1;
    }

    return 0;
}

void release_resources(int customer_num, int release[])
{
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
    {
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];
    }
}

int is_safe()
{
    int work[NUMBER_OF_RESOURCES];
    int finish[NUMBER_OF_CUSTOMERS] = {
        0,
    };

    memcpy(work, available, sizeof(int) * NUMBER_OF_RESOURCES);

    int i = 0;
    while (i < NUMBER_OF_CUSTOMERS)
    {
        if (finish[i] == 0 && compare_array(need[i], work, NUMBER_OF_RESOURCES) <= 0)
        {
            for (int j = 0; j < NUMBER_OF_RESOURCES; j++)
            {
                work[j] += allocation[i][j];
                finish[i] = 1;
            }

            i = 0;
            continue;
        }

        i++;
    }

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
    {
        if (finish[i] == 0)
            return -1;
    }

    return 0;
}

int compare_array(int *array1, int *array2, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (array1[i] > array2[i])
            return 1;
        else if (array1[i] < array2[i])
            return -1;
    }

    return 0;
}