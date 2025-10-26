#ifndef TASK_H

#define TASK_H 

typedef struct task {
    char pid[3];
    int priority;
    int cpu_burst;
} Task;

#endif 