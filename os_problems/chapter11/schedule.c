/* schedule.c
*  A program that implements the FCFS, SCAN, C-SCAN disk-scheduling algorithms.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CYLINDERS 5000
#define MAX_REQUESTS 1000

// Function prototypes
int fcfs(int *requests, int head);
int scan(int *requests, int head);
int cscan(int *requests, int head);
int compare(const void *one, const void *other);

int main(int argc, char *argv[])
{
    int head, requests[MAX_REQUESTS];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./schedule head_position\n");
        return 1;
    }

    // Get head location from the command line
    head = atoi(argv[1]);
    if (head < 0 || head >= MAX_CYLINDERS)
    {
        fprintf(stderr, "The position of the disk head should be between 0 and 4999\n");
        return 1;
    }

    //Generate random series of 1,000 cylinder requests
    srand(time(NULL));
    for (int i = 0; i < MAX_REQUESTS; i++)
        requests[i] = (int)((double)rand() / RAND_MAX * (MAX_CYLINDERS - 1));

    // Output the result
    printf("Requests: \n");
    for (int i = 0; i < MAX_REQUESTS; i++)
        printf("%d ", requests[i]);
    printf("\n");
    printf("Head position: %d\n", head);
    printf("Total amount of head movement:\n");
    printf("FCFS: %d\n", fcfs(requests, head));
    printf("SCAN: %d\n", scan(requests, head));
    printf("C-SCAN: %d\n", cscan(requests, head));

    return 0;
}

int fcfs(int *requests, int head)
{
    int total = 0;
    for (int i = 0; i < MAX_REQUESTS; i++)
    {
        total += abs(head - requests[i]);
        head = requests[i];
    }

    return total;
}

int scan(int *requests, int head)
{
    int total = 0, start = 0;
    qsort(requests, MAX_REQUESTS, sizeof(int), compare);

    while (requests[start] < head)
        start++;

    // Move right to the right end
    for (int i = start; i < MAX_REQUESTS; i++)
    {
        total += (requests[i] - head);
        head = requests[i];
    }

    total += (MAX_CYLINDERS - 1 - head);
    head = MAX_CYLINDERS - 1;

    // Move left to the left end
    for (int i = start - 1; i >= 0; i--)
    {
        total += (head - requests[i]);
        head = requests[i];
    }

    return total;
}

int cscan(int *requests, int head)
{
    int total = 0, start = 0;
    qsort(requests, MAX_REQUESTS, sizeof(int), compare);

    while (requests[start] < head)
        start++;

    // Move right to the right end
    for (int i = start; i < MAX_REQUESTS; i++)
    {
        total += (requests[i] - head);
        head = requests[i];
    }
    total += (MAX_CYLINDERS - 1 - head);
    head = MAX_CYLINDERS - 1;

    // Back to 0
    total += head;
    head = 0;

    // Move right to the right end
    for (int i = 0; i < start; i++)
    {
        total += (requests[i] - head);
        head = requests[i];
    }

    return total;
}

int compare(const void *one, const void *other)
{
    int *one_ = (int *)one;
    int *other_ = (int *)other;

    if (*one_ > *other_)
        return 1;
    else if (*one_ < *other_)
        return -1;
    else
        return 0;
}