
#include "frame.h"
#include "lru.h"
#include "LinkedList.h"
#include <string.h>

int lru_simulate(char *page_reference, int frame_nums)
{
    Frame frames;
    LinkedList pages;
    int page_table[10];
    int page_faults = 0, page_num, frame_num, replaced;

    // Initialize the page table
    for (int i = 0; i < 10; i++)
        page_table[i] = -1;

    // Initialie the frames
    init_frames(&frames, frame_nums);

    // Initialize the pages
    lru_init_pages(&pages);

    for (int i = 0, n = strlen(page_reference); i < n; i++)
    {
        page_num = page_reference[i] - '0';

        // Check if the page is on the memory
        frame_num = page_table[page_num];

        // If page fault occurs
        if (frame_num < 0)
        {
            page_faults++;

            if (frames.count < frames.length)
            {
                frame_num = frames.count;
                frames.count++;
            }
            else
            {
                replaced = lru_get_replacement(&pages);
                frame_num = page_table[replaced];
                page_table[replaced] = -1;
            }

            // Update the page table
            page_table[page_num] = frame_num;

            // Add the current page to the pages list
            AppendFromTail(&pages, &page_num, sizeof(int));
        }
        else // If page fault does not occur
        {
            // Find the page in the pages list
            Node *node = LinearSearchUnique(&pages, &page_num, compare_pages);

            // Move the page to the end of the pages list
            update_pages(&pages, node);
        }
    }

    Destroy(&pages);

    return page_faults;
}

void lru_init_pages(LinkedList *pages)
{
    Create(pages);
}

char lru_get_replacement(LinkedList *pages)
{
    int page_num;

    GetAt(pages, pages->head, &page_num, sizeof(int));
    DeleteFromHead(pages);

    return page_num;
}

void update_pages(LinkedList *pages, Node *node)
{
    if (pages->tail != node)
    {
        if (pages->head == node)
        {
            pages->head = node->next;
            node->next->previous = pages->head;
        }
        else
        {
            node->previous->next = node->next;
            node->next->previous = node->previous;
        }
        pages->tail->next = node;
        node->previous = pages->tail;
        node->next = node;
        pages->tail = node;
    }
}

int compare_pages(void *one, void *other)
{
    int *page_num1 = (int *)one;
    int *page_num2 = (int *)other;

    if (*page_num1 == *page_num2)
        return 0;
    else
        return -1;
}