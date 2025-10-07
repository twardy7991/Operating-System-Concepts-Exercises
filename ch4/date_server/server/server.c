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

// variable that defines server state.
// the static limits the variable visibility, volatile forces the compiler to reload the value every time,
// it disables the compiler optimizations on that varaible. The sig_atomic_int ensures the reading/writing
// of the value cannot be interrupted . for ex. if we use ctr+c while the is_running is being read by the 
// program, it will read it properly and then the value will be updated (no partial/dirty read).
// it is worth noting this is made for signals, not threads, thread atomicity is ensured with _Atomic.
static volatile sig_atomic_t is_running = 1;

struct ClientData {
    int client_fd;
    struct sockaddr_in client_addr;
};

void intHandler(int running);
void* handleRequest(void *arg);

/* server that waits for a request and sends the current date */
int main(void)
{   
    //create the server address
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = inet_addr("127.0.0.1"), // INADDR_ANY for my real ip
    };

    int sck_fd;

    memset(&server_addr.sin_zero, '\0', 8);

    // create a socket file descriptor
    if ((sck_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    // bind a socket to a local address specified in server_sck
    if (bind(sck_fd, (struct sockaddr *)&server_addr,  sizeof(server_addr)) == -1){
        perror("bind");
        exit(1);
    }

    // open the socket to listen for connections with the queue of size 2
    if (listen(sck_fd, 2) == -1){
        perror("listen");
        exit(1);
    }

    // bind sigint signal (ctrl +  C) to handler
    signal(SIGINT, intHandler);

    // run the server 
    while (is_running){
        pthread_t service_thread;
        struct ClientData client_data;

        socklen_t sin_size = sizeof(struct sockaddr);

        // accept connection from a client and assign the address to a variable 
        client_data.client_fd = accept(sck_fd, (struct sockaddr *)&client_data.client_addr, &sin_size);

        // create a thread that will serve the request
        if (pthread_create(&service_thread, NULL, handleRequest ,&client_data) != 0){
            perror("pthread_create");
        } else {
            printf("thread created\n");

            // wait for thread to finish serving the client 
            if (pthread_join(service_thread, NULL) != 0){
                perror("error while terminating a thread");
            };
            printf("thread terminated successfully\n");
        }
    }

    // close the server socket file descriptor 
    close(sck_fd);
    return 0;
}

// handler for sigint
void intHandler(int sig){
    is_running = 0;
}

// thread function that handles the client request
void* handleRequest(void *arg){

    struct ClientData data = *(struct ClientData*)arg;
    struct sockaddr_in client_addr = data.client_addr; 
    char *sclient_addr = inet_ntoa(client_addr.sin_addr);
    time_t currTime;
    char *scurr_Time;
    ssize_t send_bytes;

    printf("got connection from ip %s \n", sclient_addr);

    // get the current time
    time(&currTime);
    
    // cast to char
    scurr_Time = ctime(&currTime);

    printf("current time %s\n", scurr_Time);

    // send date to the client 
    if ((send_bytes = send(data.client_fd, scurr_Time, 25, 0)) == -1){
        perror("send");
        exit(1);
    }
    printf("sent bytes %d\n\n", (int)send_bytes);

    return NULL;
}


