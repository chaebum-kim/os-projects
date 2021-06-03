
#include "tlb.h"

void init_TLB()
{
    tlb.length = MAX_TLB_ENTRY;
    tlb.count = 0;
    for (int i = 0; i < MAX_TLB_ENTRY; i++)
        tlb.table[i][0] = -1;
}

int search_TLB(int page_num)
{
    for (int i = 0; i < MAX_TLB_ENTRY; i++)
    {
        if (page_num == tlb.table[i][0])
            return tlb.table[i][1];
    }
    return -1;
}

void update_TLB(int page_num, int frame_num)
{
}