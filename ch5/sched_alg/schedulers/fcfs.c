/* MODULE THAT IMPLEMENTS FIRST COME FIRST SERVED SCHEDULING ALGORITHM (FCFS) 
USING QUEUE (FIFO) */ 

#include <stdio.h>
#include "../read.h"
#include "../task.h"
#include "../cpu/cpu.h"
#include "../ds/list.h"
#include "base.h"
#include "fcfs.h"

Queue *q = NULL;

/* for now build queue handles the create_history from cpu module, 
not ideal but better than having it in main schedule module */
static int build_queue(base* me, Task* tasks, int n_task){
    create_history();
    q = create_queue(&tasks[0]);

    for (int i = 1; i < n_task; i++){
        enqueue_task(&tasks[i], q);
    }
    return 0;
}

// pick and run single task, if q is empty return NULL
static int pick_run(base* me){

    if (q->start == NULL){
        return 1;
    }

    run(dequeue_task(q) , 0);

    return 0;
}

//del queue and close history of cpu runs
static int del_queue(base* me){
    delete_queue(q);
    close_history();
    printf("queue deleted\n");
    return 0;
}

void FCFS_construct(FCFS *self){
    self->super.build_queue = build_queue;
    self->super.pick_run = pick_run;
    self->super.del_queue  = del_queue;
}