#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

Task *read_threads(char *file, int *n_tasks)
{
    Task *tasks = malloc(100);
    FILE *fptr;
    char line[100];
    char single_task[3][100];

    fptr = fopen(file, "r");

    if (fptr == NULL){
        printf("could not find the file");
        exit(1);
    }

    int n = 0;
    while (fgets(line, 100, fptr)) {
        int i = 0;
        int left = 0;
        int right = 0;
        while (i < 3){
            
            while ((line[right] != ',') && line[right] != '\0'){
                right += 1;
                continue;
            }
            memcpy(&single_task[i], &line[left], right-left);

            i += 1;
            left = right + 1;
            right += 2;
        }
        
        struct task new_task;

        memcpy(new_task.pid ,single_task[0], strlen(single_task[0]));
        new_task.pid[2] = '\0';
        new_task.priority = atoi(single_task[1]);
        new_task.cpu_burst = atoi(single_task[2]);

        tasks[n] = new_task;
        n += 1;
    }

    int i = 0;
    while (i < n){
        printf("task pid: %s, priority: %i, cpu_burst: %i \n", tasks[i].pid, tasks[i].priority, tasks[i].cpu_burst);
        i += 1;
    }

    *n_tasks = n;
    return tasks;
}


