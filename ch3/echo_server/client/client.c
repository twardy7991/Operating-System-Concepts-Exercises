#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEST_IP "127.0.0.1"

#define DEST_PORT 3490
#define MSG_LEN 10

int main(void)
{
    int sockfd_dest;
    char response[MSG_LEN];
    char msg[MSG_LEN] = "Echoo..";
    char *msg_ptr = &msg[0];

    // create server socket
    if ((sockfd_dest = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("sockfd_dest");
        exit(1);
    }

    // create server address
    struct sockaddr_in dest_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(DEST_PORT),
        .sin_addr.s_addr = inet_addr(DEST_IP)
    };

    //set padding to 0
    memset(&dest_addr.sin_zero, '\0', sizeof(dest_addr.sin_zero));

    // connect to the server
    if (connect(sockfd_dest,  (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1){
        perror("dest connect");
        exit(1);
    }

    // send the message to echo server
    if (send(sockfd_dest, msg_ptr, strlen(msg), 0) == -1){
        perror("send");
        exit(1);
    }
    ssize_t nres;
    // recieve the response from the server
    nres = recv(sockfd_dest, &response, MSG_LEN, 0);
    if (nres == -1) {
        perror("recv");
        exit(1);
    } else if (nres == 0) {
        fprintf(stderr, "server didnt respond and closed the connection\n");
    } else if (strcmp(response, msg)) {
        printf("server responses succesfully\n");
    } else {
        printf("server responded but the message was modified: %s \n", response);
    }

    // close the connection
    close(sockfd_dest);
    return 0;
}
