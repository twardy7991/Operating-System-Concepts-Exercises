// The cpu module is mimicking the cpu 

#include <stdio.h>
#include <stdlib.h>
#include "../task.h"
#include <unistd.h>

FILE *fstr;
int cpu_time;

// we save all executions to cpu_history file that tracks executions
int create_history(void){
    fstr = fopen("cpu/cpu_history.txt", "w+");
    printf("history created\n");
    return 0;
}

// write task to history 
int write_task(char *task_name, int time){
    fprintf(fstr, "%i ms : executed %s for %i ms \n", cpu_time + time, task_name, time);
    cpu_time += time;
    return 0;
}

/* run process for {time} seconds, if time is set to 0, run whole process to the end 
the 0 case is for scheduling alg that does not use time quantum */
int run(Task *task, int time){
    if (time == 0){
        time = (task->cpu_burst) * 10;
    }
    printf("run task %s, burst: %i, priority: %i \n", task->pid, task->cpu_burst, task->priority);
    usleep(time);
    write_task(task->pid, time);
    return 0;
}

int close_history(void){
    fclose(fstr);
    printf("closed history\n"); 
    return 0;
}