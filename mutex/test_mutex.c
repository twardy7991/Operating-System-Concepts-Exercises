#include <pthread.h>
#include <stdio.h>
#include "my_mutex.h"

#define COMPILER_BARRIER() asm volatile("" ::: "memory")
#define single_sum 5000000
#define final_sum (single_sum * 4)

int sum = 0;

typedef struct aruments {
    int pid;
    int* sum;
} args;

void* add(void* arg){
    
    args* arguments = arg;
    int pid = arguments->pid;
    int *sum = arguments->sum;
    for (int i = 0; i < single_sum; i++){
        acquire(pid);
        //COMPILER_BARRIER();
        *sum += 1;
        //COMPILER_BARRIER();
        release(pid);
        
    }
    printf("my pid %i\n", pid);
    return NULL;
}

int main(void){

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;

    args a1;
    args a2;
    args a3;
    args a4;

    a1.pid = 0;
    a2.pid = 1;
    a3.pid = 2;
    a4.pid = 3;
    
    a1.sum = &sum;
    a2.sum = &sum;
    a3.sum = &sum;
    a4.sum = &sum;

    pthread_create(&thread1, NULL, add, &a1);
    pthread_create(&thread2, NULL, add, &a2);
    pthread_create(&thread3, NULL, add, &a3);
    pthread_create(&thread4, NULL, add, &a4);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    
    printf("sum is %i\n", sum);
    const char* result;
    if (sum == final_sum){
        result = "true";   
    } else {
        result = "false";
    }
    printf("the sum is %s\n", result);
    return 0;
}