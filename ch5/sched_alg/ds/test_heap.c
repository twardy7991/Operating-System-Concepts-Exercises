// TESTING MODULE FOR HEAP 

#include "heap.h"
#include "../task.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../read.h"

int main(void){

    Task *list = malloc(sizeof(Task) * 8);

    int task = 8;
    list = read_threads("schedule.txt", &task);

    // int bursts[] = {1,6,7,10,5};
    // char pids[][3] = {"T1\0","T2\0","T3\0","T4\0","T5\0"};
    // int priorities[] = {1,1,1,1,1};

    // for (int i = 0; i < 5; i++){
    //     Task t = {
    //         .cpu_burst = bursts[i],
    //         .priority = priorities[i],]
    //     };
    //     strcpy(list[i].pid, pids[i]);
    //     list[i] = t;
    // }
    
    heapify(list, 8);

    for (int i = 0; i < 8; i++){
      printf("%i ," , list[i].cpu_burst);    
    }
    printf("\n");

    for (int i = 0; i < 8; i++){
      Task *min;
      if ((min = heap_extract(list)) == NULL){
        break;
      }
      printf("%i ," , min->cpu_burst);    
      printf("\n");
    }

    return 0;
}
