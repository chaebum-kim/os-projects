
#include "memory.h"
#include "size.h"
#include <stdlib.h>

void init_memory()
{
    PHYSICAL_MEMORY = FRAME_SIZE * FRAME_ENTRIES;
    memory.frame_len = FRAME_ENTRIES;
    memory.frame_count = 0;
    memory.memory = (char *)malloc(PHYSICAL_MEMORY);
}

void free_memory()
{
    free(memory.memory);
}