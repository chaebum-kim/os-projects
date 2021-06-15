
#ifndef LRU_H
#define LRU_H

#include "LinkedList.h"
#include "frame.h"

// Apply the page-reference string to LRU algorithm
int lru_simulate(char *page_reference, int frame_nums);

// Initialize pages list
void lru_init_pages(LinkedList *pages);

// Find the page to be replaced
char lru_get_replacement(LinkedList *pages);

// Move the given node to the end
void update_pages(LinkedList *pages, Node *node);

// Compare pages
int compare_pages(void *one, void *other);

#endif