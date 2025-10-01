//#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#define SERVER_PORT 3990

static volatile sig_atomic_t is_running = 1;

struct ClientData {
    int client_fd;
    struct sockaddr_in client_addr;
};

void intHandler(int running);
void* handleRequest(void *arg);

int main(void)
{
    struct sockaddr_in server_sck = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = inet_addr("127.0.0.1"), // INADDR_ANY for my real ip
    };
    memset(&server_sck.sin_zero, '\0', 8);

    int sck_fd;
    if ((sck_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    if (bind(sck_fd, (struct sockaddr *)&server_sck,  sizeof(server_sck)) == -1){
        perror("bind");
        exit(1);
    }

    if (listen(sck_fd, 2) == -1){
        perror("listen");
        exit(1);
    }

    while (is_running){
        pthread_t service_thread;

        struct ClientData client_data;

        socklen_t sin_size = sizeof(struct sockaddr);

        client_data.client_fd = accept(sck_fd, (struct sockaddr *)&client_data.client_addr, &sin_size);

        if (pthread_create(&service_thread, NULL, handleRequest ,&client_data) != 0){
            perror("pthread_create");
        } else {
            printf("thread created\n");

            if (pthread_join(service_thread, NULL) != 0){
                perror("error while terminating a thread");
            };
            printf("thread terminated successfully\n");
        }
    }
    close(sck_fd);
    return 0;
}

void intHandler(int sig){
    is_running = 0;
}

void* handleRequest(void *arg){

    struct ClientData data = *(struct ClientData*)arg;
    struct sockaddr_in client_addr = data.client_addr; 
    char *sclient_addr = inet_ntoa(client_addr.sin_addr);
    printf("got connection from ip %s \n", sclient_addr);

    time_t currTime;
    time(&currTime);
    char *scurr_Time;
    scurr_Time = ctime(&currTime);

    printf("current time %s\n", scurr_Time);

    ssize_t send_bytes;
    if ((send_bytes = send(data.client_fd, scurr_Time, 25, 0)) == -1){
        perror("send");
        exit(1);
    }
    printf("sent bytes %d\n\n", (int)send_bytes);

    return NULL;
}


