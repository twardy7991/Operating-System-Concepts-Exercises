// MODULE THAT IMPLEMENTS THE SHORTEST JOB FIRST (SJF) SCHEDULING ALGORITHM

#include <stdlib.h>
#include <stdio.h>

#include "base.h"
#include "sjf.h"
#include "../ds/heap.h"
#include "../cpu/cpu.h"

static int n_task = 0;
Task *heap_tasks;

static int build_queue(base *self, Task *tasks, int n){
    create_history();
    n_task = n;
    heap_tasks = heapify(tasks, n_task);   

    return 0;
}

static int pick_run(struct base *self){

    Task *min;
    min = heap_extract(heap_tasks);

    if (min == NULL){
        return 1; 
    }

    run(min, 0);

    return 0;
}

static int del_queue(struct base *self){
    
    free(heap_tasks);
    n_task = 0;
    close_history();
    return 0;
}

void SFJ_construct(SJF *self){
    self->super.build_queue = build_queue;
    self->super.del_queue = del_queue;
    self->super.pick_run = pick_run;
}