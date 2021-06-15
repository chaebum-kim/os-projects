
#ifndef TLB_H
#define TLB_H

#include "LinkedList.h"

#define MAX_TLB_ENTRY 16

typedef struct _tlb
{
    int count;
    int length;
    int table[MAX_TLB_ENTRY][2];
} TLB;

extern TLB tlb;

LinkedList TLB_pages;

void init_TLB();
int search_TLB(int page_num);
void update_TLB(int page_num, int frame_num);
void free_TLB();

#endif