
#include "fifo.h"
#include "frame.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int fifo_simulate(char *page_reference, int frame_nums)
{
    LinkedList pages;
    Frame frames;
    int page_table[10];
    int page_faults = 0, frame_num, page_num, replaced;

    // Initialize the page_table
    for (int i = 0; i < 10; i++)
        page_table[i] = -1;

    // Initialize the frames
    init_frames(&frames, frame_nums);

    // Initialize the pages
    fifo_init_pages(&pages);

    for (int i = 0, n = strlen(page_reference); i < n; i++)
    {
        page_num = page_reference[i] - '0';

        // Check if the page is on the memory
        frame_num = page_table[page_num];

        // If page fault occur_nums
        if (frame_num < 0)
        {
            page_faults++;

            if (frames.count < frames.length)
            {
                frame_num = frames.count;
                frames.count++;
            }
            else
            {
                replaced = fifo_get_replacement(&pages);
                frame_num = page_table[replaced];
                page_table[replaced] = -1;
            }

            // Update the page table
            page_table[page_num] = frame_num;

            // Add the current page number to the pages list
            AppendFromTail(&pages, &page_num, sizeof(int));
        }
    }

    Destroy(&pages);

    return page_faults;
}

void fifo_init_pages(LinkedList *pages)
{
    Create(pages);
}

int fifo_get_replacement(LinkedList *pages)
{
    int page_num;

    GetAt(pages, pages->head, &page_num, sizeof(int));
    DeleteFromHead(pages);

    return page_num;
}