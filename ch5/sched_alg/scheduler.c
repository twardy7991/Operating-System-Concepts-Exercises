#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "task.h"
#include "cpu/cpu.h"
#include "schedulers/base.h"
#include "schedulers/fcfs.h"
#include "schedulers/sjf.h"
#include "schedulers/rr.h"
#include "hash/hash.h"

int main(int argc, char* argv[]){
    base *obj;

    if (argc < 2){
        fprintf(stderr, "too few arguments");
        return 1;
    }

    switch (hash_djb2((unsigned char *)argv[1]))
    {
    /*fcfs*/
    case 6385217767: {
            FCFS *fcfs = malloc(sizeof(FCFS));
            FCFS_construct(fcfs);
            obj = (base*)fcfs;
            break;
        }
    /*sjf*/
    case 193505832: {
            SJF *sjf = malloc(sizeof(SJF));
            SFJ_construct(sjf);
            obj = (base*)sjf;
            break;
        }
    /*rr*/
    case 5863785: {
            RR *rr = malloc(sizeof(RR));
            RR_constructor(rr);
            obj = (base*)rr;
            break;
        }
    }
    
    int n_task = 0;
    Task *tasks = read_threads("schedule.txt", &n_task);
    printf("n_task : %i \n", n_task);
    
    obj->build_queue(obj, tasks, n_task);
    //(*obj->build_queue)(obj);

    while (1){
        if ((obj->pick_run(obj)) == 1){
            break;
        }
    }

    (*obj->del_queue)(obj);
    
    free(obj);

    return 0;
}