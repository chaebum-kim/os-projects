
#include "opt.h"
#include "frame.h"
#include <string.h>

int opt_simulate(char *reference, int frame_nums)
{
    Frame frames;
    int page_table[10];
    int page_faults = 0, page_num, frame_num, replaced;

    // Initialize the page table
    for (int i = 0; i < 10; i++)
        page_table[i] = -1;

    // Initialie the frames
    init_frames(&frames, frame_nums);

    for (int i = 0, n = strlen(reference); i < n; i++)
    {
        page_num = reference[i] - '0';

        frame_num = page_table[page_num];

        // If page fault occurs
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
                replaced = opt_get_replacement(reference, i, n, page_table);
                frame_num = page_table[replaced];
                page_table[replaced] = -1;
            }

            // Update the page table
            page_table[page_num] = frame_num;
        }
    }

    return page_faults;
}

int opt_get_replacement(char *refer, int cur, int len, int *page_table)
{
    int replaced, furthest = cur;

    for (int page_num = 0; page_num < 10; page_num++)
    {
        if (page_table[page_num] > 0)
        {
            int j = cur + 1;
            while ((j < len) && (refer[j] - '0' != page_num))
                j++;

            if (j > furthest)
            {
                furthest = j;
                replaced = page_num;
            }
        }
    }

    return replaced;
}