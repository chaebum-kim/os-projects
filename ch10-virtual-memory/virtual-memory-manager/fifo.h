#ifndef FIFO_H
#define FIFO_H

#include "LinkedList.h"

// Initialize pages list
void fifo_init_pages(LinkedList *pages);

// Add page to the pages list
void fifo_add_page(LinkedList *pages, int page_num);

// Find the page index to be replaced
int fifo_get_replacement(LinkedList *pages);

#endif