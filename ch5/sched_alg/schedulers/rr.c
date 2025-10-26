// MODULE THAT IMPLEMENTS ROUND-ROBIN SCHEDULING ALGORITHM

#include "base.h" 
#include "rr.h"
#include "../ds/list.h"
#include "../cpu/cpu.h"
#include "stdio.h"
#include "stdlib.h" 

static Queue *q;

/* the algorithm uses a time quantum to specift the maximum CPU burst
that can be assigned to single task */
static int time_quantum = 20;

static int build_queue(struct base *self, Task *tasks, int n_tasks){
    create_history();

    q = create_queue(tasks);
    for (int i = 1; i < n_tasks; i++){
        enqueue_task(&tasks[i], q);
    }

    return 0;
}

// if cpu_burst needed for task exceeds the time quantum, we requeue the task with recuded cpu_burst
static int pick_run(struct base *self){

    if (q[0].start == NULL){
        return 1;
    }

    Task *task = dequeue_task(q);
    if (task->cpu_burst <= time_quantum){
        run(task, task->cpu_burst);
    } else {
        run(task, time_quantum);
        task->cpu_burst = task->cpu_burst - time_quantum;
        enqueue_task(task, q);
    }

    return 0;
}

static int del_queue(struct base *self){
    free(q);
    close_history();

    return 0;
}

void RR_constructor(RR *self){
    self->super.build_queue = build_queue;
    self->super.del_queue = del_queue;
    self->super.pick_run = pick_run;
}



