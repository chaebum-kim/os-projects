
#ifndef MEMORY_H
#define MEMORY_H

#include "size.h"

typedef struct _memory
{
    int frame_len;
    int frame_count;
    char *memory;
} Memory;

Memory memory;

// Initialie the memory
void init_memory();

// Free memory
void free_memory();

#endif