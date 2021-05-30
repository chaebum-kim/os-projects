#include "cma.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void init_memory(ulong size)
{
    // Initialize MAX
    MAX = size;

    // Create the lists for allocations and holes
    Create(&allocations);
    Create(&holes);

    // Initialize the holes
    Hole *hole = (Hole *)malloc(sizeof(Hole));
    hole->begin = 0;
    hole->end = MAX - 1;
    hole->size = MAX;
    AppendFromTail(&holes, hole, sizeof(Hole));
}

int request_memory(char *name, ulong size, Flag flag)
{
    Allocation allocation;
    Node *index;
    Hole hole, new_hole;

    // Find availabe hole
    if (flag == F)
        index = first_fit(size);
    else if (flag == B)
        index = best_fit(size);
    else if (flag == W)
        index = worst_fit(size);

    if (index == NULL)
        return -1;

    // Retrive the hole object
    GetAt(&holes, index, &hole, sizeof(Hole));

    // Create allocation
    allocation.size = size;
    allocation.begin = hole.begin;
    allocation.end = allocation.begin + allocation.size - 1;
    strcpy(allocation.name, name);

    // Insert allocation into the list
    insert_allocation(&allocation);

    // Add new hole if necessary
    if (hole.size > allocation.size)
    {
        new_hole.size = hole.size - allocation.size;
        new_hole.begin = allocation.end + 1;
        new_hole.end = hole.end;
    }
    AppendFromTail(&holes, &new_hole, sizeof(Hole));

    // Delete the original hole
    Delete(&holes, index);

    return 0;
}

int release_memory(char *name)
{
    Allocation allocation;
    Hole new_hole;
    Node *prev = NULL, *current = First(&allocations);

    while (prev != current)
    {
        GetAt(&allocations, current, &allocation, sizeof(Allocation));
        if (strcmp(allocation.name, name) == 0)
            break;
        prev = current;
        current = Next(&allocations);
    }

    // Failed to find the process
    if (prev == current)
        return -1;

    // Delete the allocation from the list
    Delete(&allocations, current);

    // Create new hole
    new_hole.begin = allocation.begin;
    new_hole.end = allocation.end;
    new_hole.size = allocation.size;

    // Add the new hole to the list. Merge with other holes if possible.
    add_or_merge(new_hole);

    return 0;
}

void compact(void)
{
    Node *prev = NULL, *current = First(&allocations);
    Allocation *allocation;
    Hole hole;
    ulong begin = 0;

    // Push all processes to the beginning of the memory
    while (prev != current)
    {
        allocation = (Allocation *)(current + 1);
        allocation->begin = begin;
        allocation->end = allocation->begin + allocation->size - 1;
        begin = allocation->end + 1;
        prev = current;
        current = Next(&allocations);
    }

    if (begin < MAX)
    {
        // Clear holes
        DeleteAllItems(&holes);

        // Create new hole
        hole.begin = begin;
        hole.end = MAX - 1;
        hole.size = hole.end - hole.begin + 1;

        // Add new hole to the list
        AppendFromTail(&holes, &hole, sizeof(Hole));
    }
}

void report(void)
{
    ulong begin = 0;
    Node *index;
    Allocation allocation;
    Hole hole;

    while (begin < MAX)
    {
        index = LinearSearchUnique(&allocations, &begin, compare_alloc_begin);
        if (index != NULL)
        {
            GetAt(&allocations, index, &allocation, sizeof(Allocation));
            printf("Addresses [%lu:%lu] Process %s\n", allocation.begin, allocation.end, allocation.name);
            begin = allocation.end + 1;
        }
        else
        {
            index = LinearSearchUnique(&holes, &begin, compare_hole_begin);
            GetAt(&holes, index, &hole, sizeof(Hole));
            printf("Addresses [%lu:%lu] Unused\n", hole.begin, hole.end);
            begin = hole.end + 1;
        }
    }
}

Node *first_fit(ulong size)
{
    Node *prev = NULL, *current = First(&holes), *index = NULL;
    Hole hole;

    while (prev != current)
    {
        GetAt(&holes, current, &hole, sizeof(Hole));
        if (size < hole.size)
        {
            index = current;
            break;
        }
        prev = current;
        current = Next(&holes);
    }

    return index;
}

Node *best_fit(ulong size)
{
    Node *prev = NULL, *current = First(&holes), *index = NULL;
    Hole hole;
    ulong difference = 0;

    while (prev != current)
    {
        GetAt(&holes, current, &hole, sizeof(Hole));
        if (size < hole.size)
        {
            if (hole.size - size < difference || difference == 0)
            {
                difference = hole.size - size;
                index = current;
            }
        }
        prev = current;
        current = Next(&holes);
    }

    return index;
}

Node *worst_fit(ulong size)
{
    Node *prev = NULL, *current = First(&holes), *index = NULL;
    Hole hole;
    ulong difference = 0;

    while (prev != current)
    {
        GetAt(&holes, current, &hole, sizeof(Hole));
        if (size < hole.size)
        {
            if (hole.size - size > difference || difference == 0)
            {
                difference = hole.size - size;
                index = current;
            }
        }
        prev = current;
        current = Next(&holes);
    }

    return index;
}

void insert_allocation(Allocation *new_alloc)
{
    Node *prev = NULL, *current = First(&allocations);
    Allocation allocation;

    while (prev != current)
    {
        GetAt(&allocations, current, &allocation, sizeof(Allocation));
        if (compare_alloc_begin(&allocation, &(new_alloc->begin)) > 0)
            break;
        prev = current;
        current = Next(&allocations);
    }

    if (prev != current)
        InsertAfter(&allocations, current, new_alloc, sizeof(Allocation));
    else
        AppendFromTail(&allocations, new_alloc, sizeof(Allocation));
}

void add_or_merge(Hole new_hole)
{
    Node *prev = NULL, *current = First(&holes);
    Node *before = NULL, *after = NULL;
    Hole hole;

    while (prev != current)
    {
        GetAt(&holes, current, &hole, sizeof(Hole));
        if (new_hole.begin == hole.end + 1)
            before = current;
        else if (new_hole.end + 1 == hole.begin)
            after = current;
        prev = current;
        current = Next(&holes);
    }

    // Merge if possible
    if (before != NULL)
    {
        GetAt(&holes, before, &hole, sizeof(Hole));
        new_hole.begin = hole.begin;
        new_hole.size += hole.size;
        Delete(&holes, before);
    }
    if (after != NULL)
    {
        GetAt(&holes, after, &hole, sizeof(Hole));
        new_hole.end = hole.end;
        new_hole.size += hole.size;
        Delete(&holes, after);
    }

    // Add the new hole to the list
    AppendFromTail(&holes, &new_hole, sizeof(Hole));
}

int compare_alloc_begin(void *one, void *other)
{
    Allocation *allocation = (Allocation *)one;
    ulong *key = (ulong *)other;

    if (allocation->begin > *key)
        return 1;
    else if (allocation->begin == *key)
        return 0;
    else
        return -1;
}

int compare_hole_begin(void *one, void *other)
{
    Hole *hole = (Hole *)one;
    ulong *key = (ulong *)other;

    if (hole->begin > *key)
        return 1;
    else if (hole->begin == *key)
        return 0;
    else
        return -1;
}