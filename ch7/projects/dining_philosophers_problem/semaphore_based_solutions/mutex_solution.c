/* the mutex solution, enables philosophers to pick chopsticks, only when the two are available, to ensure atomicity,
we use mutexes to protect the pickup and acquire process */

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

// we introduce the mutex to protect pickup process
pthread_mutex_t m;

void pickup(int philosopher_num){
    
    while (true){

        // we get the lock for pickup process
        pthread_mutex_lock(&m);
        int right;
        int left;

        // get values of both chopsticks
        sem_getvalue(&chopsticks[philosopher_num % PHILOSOPHERS_NUM], &right);
        sem_getvalue(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM], &left);

        // check if available
        if ((right == 1) & (left == 1)){    

            // if yes, acquire and release the lock, then break and return 
            sem_wait(&chopsticks[philosopher_num]);
            sem_wait(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM]);

            pthread_mutex_unlock(&m);
            break;
        }

        // if not, release the lock and try again later
        pthread_mutex_unlock(&m);
    }
    
}

// nothing changes compared to bad solution
void putdown(int philosopher_num){
        
        sem_post(&chopsticks[philosopher_num]);
        sem_post(&chopsticks[(philosopher_num + 1) % PHILOSOPHERS_NUM]);
}

// nothing changes compared to bad solution
void* philosopher(void *params){
    pthread_mutex_init(&m, NULL);

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

// nothing changes compared to bad solution
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
