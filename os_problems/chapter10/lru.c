
#include "frame.h"
#include "lru.h"
#include "LinkedList.h"
#include <string.h>

int lru_simulate(char *page_reference, int frame_nums)
{
    Frames frames;
    LinkedList pages;
    int page_faults = 0;

    // Initialie the frames
    init_frames(&frames, frame_nums);

    // Initialize the pages
    lru_init_pages(&pages);

    for (int i = 0, n = strlen(page_reference); i < n; i++)
    {
        char page = page_reference[i], replaced;
        int index = find_page(&frames, page);

        // If page fault occurs
        if (index < 0)
        {
            page_faults++;

            if (frames.count < frames.length)
            {
                index = frames.count;
                frames.count++;
            }
            else
            {
                replaced = lru_get_replacement(&frames, &pages);
                index = find_page(&frames, replaced);
            }

            frames.frames[index] = page;

            // Add the current page to the pages list
            AppendFromTail(&pages, &page, sizeof(char));
        }
        else // If page fault does not occur
        {
            // Find the page in the pages list
            Node *node = LinearSearchUnique(&pages, &page, compare_pages);

            // Move the page to the end of the pages list
            update_pages(&pages, node);
        }
    }
    return page_faults;
}

void lru_init_pages(LinkedList *pages)
{
    Create(pages);
}

char lru_get_replacement(Frames *frames, LinkedList *pages)
{
    char page;

    GetAt(pages, pages->head, &page, sizeof(char));
    DeleteFromHead(pages);

    return page;
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
    char *page1 = (char *)one;
    char *page2 = (char *)other;

    if (*page1 == *page2)
        return 0;
    else
        return -1;
}