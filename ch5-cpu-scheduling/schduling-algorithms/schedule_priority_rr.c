#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
#include <stdlib.h>

// pick the next task
struct node *pickNextTasks(struct node *current);

void schedule()
{
    struct node *current, *newHead;

    while (head != NULL)
    {
        current = pickNextTasks(head);
        newHead = current;
        while (newHead != NULL)
        {
            Task *task = current->task;
            run(task, ((task->burst < QUANTUM) ? task->burst : QUANTUM));
            task->burst -= QUANTUM;
            if (task->burst <= 0)
            {
                delete (&newHead, task);
            }
            current = current->next;
            if (current == NULL)
                current = newHead;
        }
    }
}

void add(char *name, int priority, int burst)
{
    // Allocate the task
    Task *task = (Task *)malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = task;
    newNode->next = NULL;

    // Insert the task
    struct node *current = head;
    struct node *prev = NULL;
    while (current != NULL && current->task->priority > task->priority)
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        newNode->next = current;
        prev->next = newNode;
    }
}

struct node *pickNextTasks(struct node *current)
{
    struct node *temp;
    struct node *next = current->next;
    while (next != NULL && next->task->priority == current->task->priority)
    {
        current = current->next;
        next = current->next;
    }

    temp = head;
    head = current->next;
    current->next = NULL;

    return temp;
}