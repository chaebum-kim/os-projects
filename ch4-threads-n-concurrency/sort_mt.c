/* sort_mt.c
** A multithreaded sorting program.
*/

#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Structure for passing data to threads
typedef struct
{
    int start;
    int end;
} indexes;

// Global variables
int *array;
int *sorted_array;
int length;

// Worker functions
void *sort(void *param);
void *merge(void *param);

int main(int argc, char *argv[])
{
    int nums[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
    int half;
    pthread_t tids[3] = {0};
    pthread_attr_t attrs[3] = {0};
    indexes *data[2];

    array = nums;
    length = sizeof(nums) / sizeof(nums[0]);
    half = (int)ceil(length / 2.0);

    // Assingn data
    data[0] = (indexes *)malloc(sizeof(indexes));
    data[0]->start = 0;
    data[0]->end = half - 1;
    data[1] = (indexes *)malloc(sizeof(indexes));
    data[1]->start = half;
    data[1]->end = length - 1;

    // Set the default attributes of the threads
    for (int i = 0; i < 3; i++)
    {
        pthread_attr_init(&(attrs[i]));
    }

    // Create the sorting threads
    pthread_create(&(tids[0]), &(attrs[0]), sort, data[0]);
    pthread_create(&(tids[1]), &(attrs[1]), sort, data[1]);

    // Wait for the sorting threads to exit
    pthread_join(tids[0], NULL);
    pthread_join(tids[1], NULL);

    // Create the merging thread
    pthread_create(&(tids[2]), &(attrs[2]), merge, data[1]);

    // Wait for the merging thread to exit
    pthread_join(tids[2], NULL);

    // Print the result
    for (int i = 0; i < length; i++)
    {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

    return 0;
}

void *sort(void *param)
{
    indexes *data = (indexes *)param;
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
    indexes *data = (indexes *)param;
    int start1 = 0, end1 = data->start - 1;
    int start2 = data->start, end2 = length - 1;
    int i = 0;

    // Allocate sorted array
    sorted_array = (int *)malloc(sizeof(int) * (length));

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
