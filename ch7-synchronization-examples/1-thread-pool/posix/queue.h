#ifndef QUEUE_H
#define QUEUE_H

typedef struct _node Node;
typedef struct _node
{
    Node *next;
} Node;

typedef struct _queue
{
    Node *head;
    Node *tail;
} Queue;

void queue_create(Queue *queue);
Node *queue_enqueue(Queue *queue, void *object, size_t size);
void queue_dequeue(Queue *queue, void *object, size_t size);

#endif