#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc <= 1){
        printf("no arguments provided \n");
        return -1;
    }
    int n = atoi(argv[1]);

    if (!(n > 0)){
        printf("n is non positive :%i \n", n);
        return -1;
    }

    printf("starting number: %i \n", n);
    int pid = fork();

    if (pid < 0){
        printf("error while creating child \n");
        return -1;
    } else if(pid == 0)
    {
        while (n != 1){
            if (n % 2 == 0){
                n = n / 2; 
            }
            else{
                n = (3 * n) + 1;
            }
            printf("%i, ", n);
        }
    }
    else {
        wait(NULL);
        printf("\ncollatz reached \n");
    }
    return 0;
}