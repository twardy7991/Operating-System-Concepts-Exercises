#ifndef LIST_H

#define LIST_H

#include "../task.h"

typedef struct task_node {
    Task *task;
    struct task_node *next;
} TaskNode;

typedef struct queue {
    TaskNode *start;
    TaskNode *end;
} Queue;

Queue *create_queue(Task *first_task);

int enqueue_task(Task *task, Queue *q);

Task *dequeue_task(Queue *q);

int delete_queue(Queue *q);

#endif 