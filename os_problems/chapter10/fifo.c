
#include "fifo.h"
#include "frame.h"
#include <string.h>

int fifo_simulate(char *page_reference, int frame_nums)
{
    Frames frames;
    LinkedList pages;
    int page_faults = 0, index;
    char page;

    // Initialize the frames
    init_frames(&frames, frame_nums);

    // Initialize the pages
    fifo_init_pages(&pages);

    for (int i = 0, n = strlen(page_reference); i < n; i++)
    {
        page = page_reference[i];

        // Check if the page is on the memory
        index = find_page(&frames, page);

        // If page fault occurs
        if (index < 0)
        {
            page_faults++;

            if (frames.count < frames.length)
            {
                index = frames.count;
                frames.count++;
            }
            else
                index = fifo_get_replacement(&frames, &pages);

            frames.frames[index] = page;

            // Add the index of the current page to the pages list
            AppendFromTail(&pages, &index, sizeof(int));
        }
    }

    return page_faults;
}

void fifo_init_pages(LinkedList *pages)
{
    Create(pages);
}

int fifo_get_replacement(Frames *frames, LinkedList *pages)
{
    int index;

    GetAt(pages, pages->head, &index, sizeof(int));
    DeleteFromHead(pages);

    return index;
}
