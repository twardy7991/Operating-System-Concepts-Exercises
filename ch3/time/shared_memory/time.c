#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

/* the program aims to display a command execution time, the command will be executed by a child process and it will write start execution time to a shared memory */
int main(int argc, char *argv[])
{
    char *process; 
    pid_t pid;
    struct timeval tv_start;
    const int SIZE = 4096;
    const char *name = "TIME";

    int fd;
    char *ptr;

    /* creating a shared memory object */
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    /* as it has no size, we set it to 4096 bytes */
    ftruncate(fd, SIZE);
    /* map the shm into a process address space */
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    process = argv[1];
    pid = fork();

    if (pid < 0){
        fprintf(stderr ,"could not create the process");
        return 1;
    }
    else if (pid == 0){
        /* getting current time */
        gettimeofday(&tv_start, NULL);

        printf("child start %ld %ld", tv_start.tv_sec, tv_start.tv_usec);

        /* wrinting the values to a shm */
        sprintf(ptr, "%ld %ld", tv_start.tv_sec, tv_start.tv_usec);

        /* excecuting the provided command */
        execlp(process, process, NULL);

    }
    else if (pid > 0) {
        time_t sec_start;
        time_t sec_stop;
        suseconds_t usec_start;
        suseconds_t usec_stop;
        struct timeval tv_stop;
        
        pid_t child_exit = wait(NULL);

        /* getting the current time */
        gettimeofday(&tv_stop, NULL);

        if (child_exit == pid){

            /* get the values from a shared memory*/
            sscanf(ptr, "%ld %ld", &sec_start, &usec_start);
            sec_stop = tv_stop.tv_sec;
            usec_stop = tv_stop.tv_usec;

            /* calculate ms difference */
            long long start_us = (long long)sec_start * 1000000LL + usec_start;
            long long stop_us  = (long long)sec_stop  * 1000000LL + usec_stop;
            printf("Start: %lld \n", start_us);
            printf("Stop: %lld \n", stop_us);

            long long duration = stop_us - start_us;
            printf("Duration %lld \n", duration);
        }
        else {
            printf("child returned an error");
            /*does the same as below*/
            munmap(ptr, SIZE);      
            close(fd);             
            shm_unlink("TIME");
            return 1;
        }
    }
    /* unmapping the virtual memory */
    munmap(ptr, SIZE);
    /* closing the file descriptor for my process */
    close(fd);             
    /* remove the shared memory object "TIME" */
    shm_unlink("TIME");
    return 0;
}
