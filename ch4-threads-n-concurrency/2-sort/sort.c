/* sort`.c
*  A multithreaded sorting application
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int sort(int *nums, int *sorted_nums, size_t size)
{
    int half = size / 2;
    pthread_t tids[3];
    Range *data[2];

    // Set the global variables
    array = nums;
    sorted_array = sorted_nums;

    // Assingn data
    data[0] = (Range *)malloc(sizeof(Range));
    data[0]->start = 0;
    data[0]->end = half - 1;
    data[1] = (Range *)malloc(sizeof(Range));
    data[1]->start = half;
    data[1]->end = size - 1;

    // Create the sorting threads
    pthread_create(&(tids[0]), NULL, partial_sort, data[0]);
    pthread_create(&(tids[1]), NULL, partial_sort, data[1]);

    // Wait for the sorting threads to exit
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);

    // Create the merging thread
    pthread_create(&(tids[2]), NULL, merge, data[1]);

    // Wait for the merging thread to exit
    pthread_join(tids[2], NULL);

    // Free data
    for (int i = 0; i < 2; i++)
        free(data[i]);

    return 0;
}

void *partial_sort(void *param)
{
    Range *data = (Range *)param;
    int start = data->start, end = data->end;

    for (int i = start; i <= end; i++)
    {
        for (int j = i + 1; j <= end; j++)
        {
            if (array[i] > array[j])
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    pthread_exit(0);
}

void *merge(void *param)
{
    Range *data = (Range *)param;
    int start1 = 0, end1 = data->start - 1;
    int start2 = data->start, end2 = data->end;
    int i = 0;

    // Merge
    while (start1 <= end1 && start2 <= end2)
    {
        if (array[start1] < array[start2])
        {
            sorted_array[i] = array[start1];
            start1++;
        }
        else
        {
            sorted_array[i] = array[start2];
            start2++;
        }
        i++;
    }
    while (start1 <= end1)
    {
        sorted_array[i] = array[start1];
        start1++;
        i++;
    }
    while (start2 <= end2)
    {
        sorted_array[i] = array[start2];
        start2++;
        i++;
    }

    pthread_exit(0);
}
