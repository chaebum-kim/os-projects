
#include "fifo.h"
#include "lru.h"
#include "opt.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STRING 32

int main(int argc, char *argv[])
{
    int frame_nums;
    char reference[MAX_STRING + 1];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./main #_of_page_frames\n");
        return 1;
    }

    // Get the command line argument
    frame_nums = atoi(argv[1]);

    // Generate a random page-reference string
    srand(time(NULL));
    for (int i = 0; i < MAX_STRING; i++)
    {
        int page = (int)((double)rand() / RAND_MAX * 9);
        reference[i] = page + '0';
    }
    reference[MAX_STRING] = '\0';

    // Output the result
    printf("-------------------------------------------------------------------\n");
    printf("Page-reference string: %s\n", reference);
    printf("-------------------------------------------------------------------\n");
    printf("The number of page faults occured:\n");
    printf("FIFO: %d\n", fifo_simulate(reference, frame_nums));
    printf("LRU: %d\n", lru_simulate(reference, frame_nums));
    printf("OPT: %d\n", opt_simulate(reference, frame_nums));
    printf("-------------------------------------------------------------------\n");

    return 0;
}