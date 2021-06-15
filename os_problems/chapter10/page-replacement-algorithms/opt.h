
#ifndef OPT_H
#define OPT_H

#include "frame.h"

// Apply the page-reference string to OPT algorithm
int opt_simulate(char *reference, int frame_nums);

// Find the index of the page to be replaced in the frames
int opt_get_replacement(char *refer, int cur, int len, int *page_table);

#endif