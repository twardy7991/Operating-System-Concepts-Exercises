// MODULE IMPLEMENTS A QUEUE USING LINKED LIST DATA STRUCTURE (FIFO)

#include <stdlib.h>
#include <stdio.h>

#include "../task.h"
#include "list.h"

Queue *create_queue(Task *first_task){
    TaskNode *start_node = malloc(sizeof(TaskNode));
    start_node->task = first_task;
    start_node->next = NULL;
    
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->start = start_node;
    q->end = start_node;

    printf("queue created\n");

    return q;
}

int enqueue_task(Task *task, Queue *q){
    TaskNode *curr_end = q->end;

    TaskNode *new_node = malloc(sizeof(TaskNode)); 
    new_node->task = task,
    new_node->next = NULL,
  
    curr_end->next = new_node;
    q->end = new_node;

    return 0;
}

Task *dequeue_task(Queue *q){
    TaskNode first_node;

    if (q->start == NULL){
        return NULL;
    } else if (q->start == q->end){
        first_node = *q->start;
        q->start = NULL;
        q->end = NULL;
    } else { 
        first_node = *q->start;
        q->start = first_node.next;
    }
    return first_node.task;
}

int delete_queue(Queue *q){
    TaskNode *head = q->start;

    Queue null_q = {
        .start = NULL,
        .end = NULL,
    };

    TaskNode null_node = {
        .next = NULL,
        .task = NULL,
    };

    if (null_q.start == q->start && null_q.end == q->end){
        free(q);
        return 0;
    }

    TaskNode *next;
    while (head->next != null_node.next){
        next = head->next;
        free(head);
        head = next;
    }

    free(q);
    return 0;
}

