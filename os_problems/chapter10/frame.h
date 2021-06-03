
#ifndef FRAME_H
#define FRAME_H

typedef struct _frame
{
    int length;
    int count;
} Frame;

// Initialie the frames
void init_frames(Frame *frames, int frame_nums);

#endif
