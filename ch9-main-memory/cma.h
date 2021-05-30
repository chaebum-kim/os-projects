#ifndef CMA_H
#define CMA_H

#include "LinkedList.h"

#define MAX_NAME 4

LinkedList allocations;
LinkedList holes;

typedef unsigned long ulong;

typedef struct _allocation
{
    ulong begin;
    ulong end;
    ulong size;
    char name[MAX_NAME];
} Allocation;

typedef struct _hole
{
    ulong begin;
    ulong end;
    ulong size;
} Hole;

typedef enum _flag
{
    F,
    B,
    W
} Flag;

ulong MAX;

void init_memory(ulong size);
int request_memory(char *name, ulong size, Flag flag);
int release_memory(char *name);
void compact(void);
void report(void);

Node *first_fit(ulong size);
Node *best_fit(ulong size);
Node *worst_fit(ulong size);

void insert_allocation(Allocation *allocation);
void add_or_merge(Hole new_hole);

int compare_alloc_begin(void *one, void *other);
int compare_hole_begin(void *one, void *other);

#endif