
#include "opt.h"
#include "frame.h"
#include <string.h>

int opt_simulate(char *reference, int frame_nums)
{
    Frames frames;
    int page_faults = 0;

    // Initialie the frames
    init_frames(&frames, frame_nums);

    for (int i = 0, n = strlen(reference); i < n; i++)
    {
        char page = reference[i];
        int index = find_page(&frames, page);

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
                index = opt_get_replacement(reference, i, n, &frames);

            frames.frames[index] = page;
        }
    }

    return page_faults;
}

int opt_get_replacement(char *refer, int cur, int len, Frames *frames)
{
    int furthest = 0, frame_index;

    for (int i = 0; i < frames->count; i++)
    {
        char page = (frames->frames)[i];
        int temp = cur + 1;
        while (temp <= len && page != refer[temp])
            temp++;

        if (temp > furthest)
        {
            furthest = temp;
            frame_index = i;
        }

        if (furthest > len)
            break;
    }

    return frame_index;
}