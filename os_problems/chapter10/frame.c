
#include "frame.h"

void init_frames(Frames *frames, int frame_nums)
{
    frames->length = frame_nums;
    frames->count = 0;
    frames->frames = (char *)malloc(frames->length * sizeof(char));
}

int find_page(Frames *frames, char key)
{
    for (int i = 0; i < frames->count; i++)
    {
        if ((frames->frames)[i] == key)
            return i;
    }
    return -1;
}