/*the max4 solution enables only n-1 philosophers to sit at the table (we have total of n philosophers), 
this creates a situation, where one philosopher is guaranteed to have two chopsticks available for him */

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

// we introduce a semaphore to track the philosophers that try to get chopsticks 
sem_t queue;

void pickup(int philosopher_num);
void putdown(int philosopher_num);
void* philosopher(void *params);
int main(int argc, char* argcv[]);

// nothing changes compared to bad solution
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


void pickup(int philosopher_num){
    // we wait to get into the queue and start eating
    sem_wait(&queue);
    
    sem_wait(&chopsticks[philosopher_num % PHILOSOPHERS_NUM]);            
    sem_wait(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM]);

}

void putdown(int philosopher_num){

    sem_post(&chopsticks[philosopher_num]);
    sem_post(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM]);

    // we release the semaphore and "quit" the queue
    sem_post(&queue);
}

int main(int argc, char* argcv[]){

    /* create a queue semaphore with initial value PHILOSOPHERS_NUM - 1, 
    so that at most n - 1 philosophers can "eat" at once  */
    sem_init(&queue, 0, PHILOSOPHERS_NUM - 1);

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

    sem_destroy(&queue);

    printf("\nPHILOSOPHERS done\n");
    return 0;
}
