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

void sigIntHandler(int sig){
    printf("Caught signal %d\n", sig);

    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        sem_destroy(&chopsticks[i]);
    }

    exit(sig);
}

void* philosopher(void *params){

    int philosopher_num = *(int *) params;
    free(params);

    for (int i = 0; i < 100; i ++){
            __useconds_t think = rand() % 10 + 10;
            __useconds_t consume = rand() % 10 + 10;

            usleep(think);

            printf("philosopher %i takes %i chopstick\n", philosopher_num, philosopher_num % PHILOSOPHERS_NUM);
            sem_wait(&chopsticks[philosopher_num % PHILOSOPHERS_NUM]);
            printf("philosopher %i takes %i chopstick\n", philosopher_num, (philosopher_num + 1) % PHILOSOPHERS_NUM);
            sem_wait(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM]);

            usleep(consume);

            printf("philosopher %i releases %i chopstick\n", philosopher_num, philosopher_num % PHILOSOPHERS_NUM);
            sem_post(&chopsticks[philosopher_num]);
            printf("philosopher %i releases %i chopstick\n", philosopher_num, (philosopher_num + 1) % PHILOSOPHERS_NUM);
            sem_post(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM]);
        }
        printf("\nPHILOSOPHER %i done\n", philosopher_num);

        return NULL;
    }

int main(int argc, char* argcv[]){

    signal(SIGINT, sigIntHandler);

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
