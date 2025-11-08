// This is a simple solution with semaphores, that can result in a deadlock, it is a base for other, correct solutions
//
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

void pickup(int philosopher_num);
void putdown(int philosopher_num);
void* philosopher(void *params);
int main(int argc, char* argcv[]);

//the function exectes the think -> eat -> think... etc. routine. It uses random microseconds intervals
void* philosopher(void *params){

    int philosopher_num = *(int *) params;
    free(params);

    for (int i = 0; i < 100; i ++){
        __useconds_t think = rand() % 10 + 10;
        __useconds_t consume = rand() % 10 + 10;

        // think and try to take chopsticks
        usleep(think);
        pickup(philosopher_num);

        // consume and release
        usleep(consume);
        putdown(philosopher_num);

    }
    printf("\nPHILOSOPHER %i done\n", philosopher_num);

    return NULL;
    }

//function that takes number of the philosopher and tries to obtain the chopsticks next to the philosopher 
void pickup(int philosopher_num){
    int left = philosopher_num % PHILOSOPHERS_NUM;
    int right = (philosopher_num + 1) % PHILOSOPHERS_NUM;
    sem_wait(&chopsticks[left]);            
    sem_wait(&chopsticks[right]);

}

//function that takes number of the philosopher and releases the chopsticks next to the philosopher 
void putdown(int philosopher_num){
    sem_post(&chopsticks[philosopher_num]);
    sem_post(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM]);

}

int main(int argc, char* argcv[]){

    //init chopstick semaphores
    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        sem_init(&chopsticks[i], 0, 1);
    }

    // initialize threads and pass philosopher_num
    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        int *param = malloc(sizeof(int));
        *param = i;
        pthread_create(&philosophers[i], NULL, philosopher, param);
    }

    // wait for all threads
    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        pthread_join(philosophers[i], NULL);
    }

    // destroy all semaphores
    for (int i = 0; i < PHILOSOPHERS_NUM; i++){
        sem_destroy(&chopsticks[i]);
    }

    printf("\nPHILOSOPHERS done\n");
    return 0;
}
