
#ifndef SORT_H
#define SORT_H

// Structure for passing data to threads
typedef struct
{
    int start;
    int end;
} Range;

// Global variable
int *array;
int *sorted_array;

int sort(int *nums, int *sorted_nums, size_t size);
void *partial_sort(void *param);
void *merge(void *param);

#endif