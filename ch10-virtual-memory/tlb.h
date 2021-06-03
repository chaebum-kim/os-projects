
#ifndef TLB_H
#define TLB_H

#define MAX_TLB_ENTRY 16

typedef struct _tlb
{
    int count;
    int length;
    int table[MAX_TLB_ENTRY][2];
} TLB;

TLB tlb;

void init_TLB();
int search_TLB(int page_num);
void update_TLB(int page_num, int frame_num);

#endif