
#ifndef FRAME_H
#define FRAME_H

#include <stdlib.h>

typedef struct _frames
{
    int length;
    int count;
    char *frames;
} Frames;

// Initialie the frames
void init_frames(Frames *frames, int frame_nums);

// Find the page in frames
int find_page(Frames *frames, char page);

#endif
