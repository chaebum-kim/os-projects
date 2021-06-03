
#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H

#include "size.h"

int page_table[PAGE_ENTRIES];

void init_table();

int search_table(int page_num);

#endif