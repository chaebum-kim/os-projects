#include <stdlib.h>
#include <memory.h>
#include "queue.h"

void queue_create(queue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
}

int is_empty(queue *queue)
{
    if (queue->head == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

node *queue_enqueue(queue *queue, void *object)
{
    node *temp = NULL;
    temp = (node *)malloc(sizeof(node) + sizeof(*object));

    if (temp == NULL)
    {
        return NULL;
    }

    memcpy(temp + 1, object, sizeof(*object));

    temp->next = NULL;

    if (queue->tail == NULL)
    {
        queue->head = temp;
        queue->tail = temp;
    }
    else
    {
        queue->tail->next = temp;
        queue->tail = temp;
    }

    return queue->tail;
}

void queue_dequeue(queue *queue, void *object)
{
    memcpy(object, queue->head + 1, sizeof(*object));
    node *temp = queue->head->next;
    free(queue->head);
    queue->head = temp;
}
