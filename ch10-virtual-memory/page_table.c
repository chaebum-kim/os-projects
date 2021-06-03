
#include "page_table.h"

void init_table()
{
    for (int i = 0; i < PAGE_ENTRIES; i++)
        page_table[i] = -1;
}

int search_table(int page_num)
{
    return page_table[page_num];
}