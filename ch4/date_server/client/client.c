#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PORT 3990
#define MSG_SIZE 100

/* the client sends request to server and expects to receive today's date */
int main(void)
{
    // create server socket address
    struct sockaddr_in server_sck = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(SERVER_PORT)
    };

    // padding that makes the server more compatible with .. (?)
    memset(server_sck.sin_zero, '\0', 8);

    int sck_fd; 
    int success;
    char msg[100];
    int msg_len;

    // create a socket dile descriptor
    if ((sck_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    // open a connection to a server on previously created socket
    if ((success = connect(sck_fd, (struct sockaddr *)&server_sck, sizeof(struct sockaddr))) == -1){
        perror("connect");
        exit(1);
    };

    // wait and save the response from server
    msg_len = recv(sck_fd, msg, 25,  0);

    printf("got date: %.*s\n", msg_len, msg);

    // close the fd
    close(sck_fd);
    return 0;
}