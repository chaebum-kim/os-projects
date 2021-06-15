
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"
#include <stdlib.h>

// pick the next task
Task *pickNextTask(struct node *head);

void schedule()
{
    while (head != NULL)
    {
        Task *task = pickNextTask(head);
        delete (&head, task);
        run(task, task->burst);
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