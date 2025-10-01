#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 3990
#define MSG_SIZE 100

int main(void)
{

    struct sockaddr_in server_sck = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(SERVER_PORT)
    };

    int sck_fd;

    if ((sck_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    int success;

    if ((success = connect(sck_fd, (struct sockaddr *)&server_sck, sizeof(struct sockaddr))) == -1){
        perror("connect");
        exit(1);
    };

    char msg[100];
    int msg_len;
    msg_len = recv(sck_fd, msg, 25,  0);

    printf("got date: %.*s\n", msg_len, msg);
    close(sck_fd);
    return 0;
}