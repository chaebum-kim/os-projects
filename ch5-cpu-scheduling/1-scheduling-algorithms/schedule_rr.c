#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
#include <stdlib.h>

// pick the next task
Task *pickNextTask(struct node *head);

void schedule()
{
    struct node *current = head;
    while (current != NULL)
    {
        Task *task = pickNextTask(current);
        run(task, ((task->burst < QUANTUM) ? task->burst : QUANTUM));
        task->burst -= QUANTUM;
        if (task->burst <= 0)
        {
            delete (&head, task);
        }
        current = current->next;
        if (current == NULL)
            current = head;
    }
}

void add(char *name, int priority, int burst)
{
    // Allocate the task
    Task *task = (Task *)malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;

    // Insert the task
    insert(&head, task);
}

Task *pickNextTask(struct node *current)
{
    return current->task;
}