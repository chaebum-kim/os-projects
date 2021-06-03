
#include "size.h"
#include "memory.h"
#include "page_table.h"
#include "tlb.h"
#include <stdio.h>
#include <stdlib.h>

// Helper functions
void extract(ushort address, ushort *page_num, ushort *offset);

int main(int argc, char *argv[])
{
    ushort virtual, physical, page_num, offset;
    int frame_num, page_faults = 0, tlb_hits = 0, total = 0;

    // Initialie the memory, page table, and TLB
    init_memory();
    init_table();
    init_TLB();

    // Open the file
    FILE *file = fopen("addresses.txt", "r");

    if (file == NULL)
        return 1;

    while (!feof(file) && fscanf(file, "%hd", &virtual) > 0)
    {
        // Count the page
        total++;

        // Extract the page number and offset
        extract(virtual, &page_num, &offset);

        // Find the page in TLB
        frame_num = search_TLB(page_num);

        // If TLB hits
        if (frame_num > 0)
            tlb_hits++;
        else
            // Find the page in the page table
            frame_num = search_table(page_num);

        // If page fault occurs
        if (frame_num < 0)
        {
            page_faults++;

            if (memory.frame_count < memory.frame_len)
            {
                frame_num = memory.frame_count;
                memory.frame_count++;
            }

            // Update the page table
            page_table[page_num] = frame_num;

            // Update TLB
            //TODO
        }

        physical = frame_num * FRAME_SIZE + offset;
        printf("Virtual address: %d, Physical address: %d, Value: %d\n", virtual, physical, memory.memory[physical]);
    }

    // Close the file
    fclose(file);

    // Free memory
    free_memory();

    // Output the statistics
    printf("------------------------------------------------------------------\n");
    printf("Page-fault rate: %.2f, TLB hit rate: %.2f\n", (float)page_faults / total, (float)tlb_hits / total);

    return 0;
}

void extract(ushort address, ushort *page_num, ushort *offset)
{
    ushort mask1 = (1 << 16) - 1, mask2 = (1 << 8) - 1;
    address &= mask1;
    *offset = mask2 & address;
    address >>= 8;
    *page_num = mask2 & address;
}