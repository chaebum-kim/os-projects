#ifndef FIFO_H
#define FIFO_H

#include "LinkedList.h"
#include "frame.h"

// Apply the page-reference string to FIFO algorithm
int fifo_simulate(char *page_reference, int frame_nums);

// Initialize pages list
void fifo_init_pages(LinkedList *pages);

// Find the page index to be replaced
int fifo_get_replacement(LinkedList *pages);

#endif