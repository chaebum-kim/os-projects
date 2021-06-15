
#include "backstore.h"
#include "size.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

int read_n_store(int page_num, int frame_num)
{
    FILE *file = fopen("BACKING_STORE.bin", "r");
    char *address;

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open the backing store.\n");
        return -1;
    }

    fseek(file, page_num * PAGE_SIZE, SEEK_SET);

    address = memory.memory + frame_num * FRAME_SIZE;

    fread(address, PAGE_SIZE, 1, file);

    fclose(file);

    return 0;
}