
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include <signal.h>

#define MYPORT 3490
#define BACKLOG 10

int main(void){

    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    char msg[10];
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    ssize_t nread;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
    }

    my_addr.sin_family = AF_INET; //host byte order
    my_addr.sin_port = htons(MYPORT); // short, network byte order
    my_addr.sin_addr.s_addr = INADDR_ANY; // my id address

    // zero'ing the padding
    memset(&(my_addr.sin_zero), '\0', 8);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct  sockaddr)) == -1 ) {
        perror("bind");
        exit(1);
    };

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    // sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    sin_size = sizeof(struct sockaddr_in);

    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
        perror("accept");
        exit(1);
    }

    printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
    
    while (1) {
        nread = recv(new_fd, &msg, sizeof(msg), 0);  
        if (nread == -1) {
            perror("recv");
            exit(1);
        } else if (nread == 0) {
            printf("client closed the connection");
            close(sockfd);
            close(new_fd);
            return 0;
        } else {
            send(new_fd, &msg, sizeof(msg), 0);
        }

        close(sockfd);
        close(new_fd);
        return 0;
    }
}