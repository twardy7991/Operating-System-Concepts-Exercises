/*
asymmetric solution controls the order, in which chopsticks are approached,
even philophers take the left choopstick first while the odd take the right,
this way neighbour philosophers both will try to pick same chopstick as first, 
or both as second. In the first case, one of them wins and then will try with second chopstick,
which is the second scenario, here also one of the philosophers win. 
It results in a situation where at least one of the philosophers have to win -> no deadlock.

the code below implements the idea
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h> 
#include <signal.h> 

#define PHILOSOPHERS_NUM 5

sem_t chopsticks[PHILOSOPHERS_NUM];
pthread_t philosophers[PHILOSOPHERS_NUM];

void pickup(int philosopher_num){
    int left = philosopher_num % PHILOSOPHERS_NUM;
    int right = (philosopher_num + 1) % PHILOSOPHERS_NUM;

    // if the philosopher is even, he picks up the left first
    if (philosopher_num % 2 == 0){
        sem_wait(&chopsticks[left]);
        sem_wait(&chopsticks[right]);
    // if the philosopher is even, he picks up the right first
    } else {
        sem_wait(&chopsticks[right]);
        sem_wait(&chopsticks[left]);
    }
}   

// the release order is not imortant
void putdown(int philosopher_num){
    int left = philosopher_num % PHILOSOPHERS_NUM;
    int right = (philosopher_num + 1) % PHILOSOPHERS_NUM;

    sem_post(&chopsticks[right]);
    sem_post(&chopsticks[left]);

}

// nothing changed compared to bad solution
void* philosopher(void *params){

    int philosopher_num = *(int *) params;
    free(params);

    for (int i = 0; i < 100; i ++){
            __useconds_t think = rand() % 10 + 10;
            __useconds_t consume = rand() % 10 + 10;

            usleep(think);
            pickup(philosopher_num);

            usleep(consume);
            putdown(philosopher_num);

        }
        printf("\nPHILOSOPHER %i done\n", philosopher_num);

        return NULL;
    }

// nothing changed compared to bad solution
int main(int argc, char* argcv[]){

    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        int *param = malloc(sizeof(int));
        *param = i;
        pthread_create(&philosophers[i], NULL, philosopher, param);
    }

    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        sem_destroy(&chopsticks[i]);
    }

    printf("\nPHILOSOPHERS done\n");
    return 0;
}
