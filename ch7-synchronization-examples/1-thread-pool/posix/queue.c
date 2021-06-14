#include <stdlib.h>
#include <memory.h>
#include "queue.h"

void queue_create(Queue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
}

Node *queue_enqueue(Queue *queue, void *object, size_t size)
{
    Node *temp = NULL;
    temp = (Node *)malloc(sizeof(Node) + size);

    if (temp == NULL)
        return NULL;

    memcpy(temp + 1, object, size);

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

void queue_dequeue(Queue *queue, void *object, size_t size)
{
    memcpy(object, queue->head + 1, size);
    Node *temp = queue->head->next;

    free(queue->head);

    if (temp == NULL)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }
    else
        queue->head = temp;
}
