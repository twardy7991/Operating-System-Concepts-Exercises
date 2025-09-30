#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#define BUFFER_SIZE 50

/* the program aims to display a command execution time, the command will be executed by a child process and it will write start execution time to a pipe */
int main(int argc, char *argv[])
{
    char *process; 
    pid_t pid;
    struct timeval tv_start;
    const int SIZE = 4096;
    const char *name = "TIME";

    int fd;
    char *ptr;
    int pipefd[2];

    /* we create a pipe with pointer to a integer array of size two, each int is a file descriptor for input (pipefd[1]), output (pipefd[0])*/
    if (pipe(&pipefd) < 0){
        exit(1);
    }

    process = argv[1];
    /* fork a child process*/
    pid = fork();

    if (pid < 0){
        fprintf(stderr ,"could not create the process");
        return 1;
    }
    else if (pid == 0){
        /* close the output end of pipe, as we dont need it */
        close(pipefd[0]);

        /* get current time */
        gettimeofday(&tv_start, NULL);

        printf("child start %ld %ld", tv_start.tv_sec, tv_start.tv_usec);

        /* write to a pipe */
        write(pipefd[1], &tv_start, sizeof(tv_start));

        /*excecute a provided command */
        execlp(process, process, NULL);

    }
    else if (pid > 0) {
        /* close the input end of pipe, as we dont need it */
        close(pipefd[1]);

        time_t sec_start;
        time_t sec_stop;
        suseconds_t usec_start;
        suseconds_t usec_stop;
        struct timeval tv_stop;
        
        /* wait for child to finish executing */
        pid_t child_exit = wait(NULL);

        /* get current time */
        gettimeofday(&tv_stop, NULL);

        /* if child finished succesfully, read and calculate the command execution duration*/
        if (child_exit == pid){
            
            /* read from the pipe */
            read(pipefd[0], &tv_start, sizeof(tv_start));
            sec_stop = tv_stop.tv_sec;
            usec_stop = tv_stop.tv_usec;
            sec_start = tv_start.tv_sec;
            usec_start = tv_start.tv_usec;

            /* calculate time difference for both seconds and microseconds */
            long long start_us = (long long)sec_start * 1000000LL + usec_start;
            long long stop_us  = (long long)sec_stop  * 1000000LL + usec_stop;

            printf("Start: %lld \n", start_us);
            printf("Stop: %lld \n", stop_us);

            long long duration = stop_us - start_us;
            /* print the duration in microseconds*/
            printf("Duration %lld ms\n", duration);
        }
        else {
            printf("child returned an error");
            return 1;
        }
    }
    return 0;
}
