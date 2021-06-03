
#include "tlb.h"
#include "fifo.h"

void init_TLB()
{
    // Initialize TLB
    tlb.length = MAX_TLB_ENTRY;
    tlb.count = 0;
    for (int i = 0; i < MAX_TLB_ENTRY; i++)
        tlb.table[i][0] = -1;

    // Initialize TLB pages
    fifo_init_pages(&TLB_pages);
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
    if (tlb.count < tlb.length)
    {
        tlb.table[tlb.count][0] = page_num;
        tlb.table[tlb.count][1] = frame_num;
        tlb.count++;
    }
    else
    {
        int replaced = fifo_get_replacement(&TLB_pages);

        for (int i = 0; i < tlb.count; i++)
        {
            if (tlb.table[i][0] == replaced)
            {
                tlb.table[i][0] = page_num;
                tlb.table[i][1] = frame_num;
                break;
            }
        }
    }

    fifo_add_page(&TLB_pages, page_num);
}

void free_TLB()
{
    Destroy(&TLB_pages);
}