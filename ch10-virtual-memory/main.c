
#include "size.h"
#include "memory.h"
#include "page_table.h"
#include "tlb.h"
#include "fifo.h"
#include "backstore.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

// Helper functions
void extract(ushort address, ushort *page_num, ushort *offset);
void page_fault_routine(int page_num, int *frame_num);

// Global variables
Memory memory;
TLB tlb;
LinkedList replacements;
int page_table[PAGE_ENTRIES];

int main(int argc, char *argv[])
{
    ushort virtual, physical, page_num, offset;
    int frame_num, page_faults = 0, tlb_hits = 0, total = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./main filename\n");
        return 1;
    }

    // Initialie the memory, page table, TLB, replacements
    init_memory();
    init_table();
    init_TLB();
    fifo_init_pages(&replacements);

    // Open the file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open the file.\n");
        return 1;
    }

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
            page_fault_routine(page_num, &frame_num);
        }

        // Calculate an physical address of the memory
        physical = frame_num * FRAME_SIZE + offset;
        printf("Virtual address: %d, Physical address: %d, Value: %d\n", virtual, physical, memory.memory[physical]);
    }

    // Close the file
    fclose(file);

    // Free memory, TLB, replacements
    free_memory();
    free_TLB();
    Destroy(&replacements);

    // Output the statistics
    printf("------------------------------------------------------------------\n");
    printf("Page-fault rate: %.2f, TLB hit rate: %.2f\n", (float)page_faults / total, (float)tlb_hits / total);

    return 0;
}

void page_fault_routine(int page_num, int *frame_num)
{
    // Get an available frame from the memory
    if (memory.frame_count < memory.frame_len)
    {
        *frame_num = memory.frame_count;
        memory.frame_count++;
    }
    else // Replace the page if there is no available frame
    {
        int replaced = fifo_get_replacement(&replacements);
        *frame_num = page_table[replaced];
        page_table[replaced] = -1;
    }

    // Read page from the the backing store and store it in the memory
    read_n_store(page_num, *frame_num);

    // Add the current page to the replacements list
    fifo_add_page(&replacements, page_num);

    // Update the page table
    page_table[page_num] = *frame_num;

    // Update TLB
    update_TLB(page_num, *frame_num);
}

void extract(ushort address, ushort *page_num, ushort *offset)
{
    ushort mask1 = (1 << 16) - 1, mask2 = (1 << 8) - 1;
    address &= mask1;
    *offset = mask2 & address;
    address >>= 8;
    *page_num = mask2 & address;
}