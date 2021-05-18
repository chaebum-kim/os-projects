#ifndef QUEUE
#define QUEUE

typedef struct _node node;
typedef struct _node
{
    node *next;
} node;

typedef struct queue
{
    node *head;
    node *tail;
} queue;

void queue_create(queue *queue);
int is_empty(queue *queue);
node *queue_enqueue(queue *queue, void *object);
void queue_dequeue(queue *queue, void *object);

#endif