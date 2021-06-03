
#include "fifo.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void fifo_init_pages(LinkedList *pages)
{
    Create(pages);
}

void fifo_add_page(LinkedList *pages, int page_num)
{
    AppendFromTail(pages, &page_num, sizeof(int));
}

int fifo_get_replacement(LinkedList *pages)
{
    int page_num;

    GetAt(pages, pages->head, &page_num, sizeof(int));
    DeleteFromHead(pages);

    return page_num;
}