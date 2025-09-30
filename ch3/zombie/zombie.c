#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

/* the task is to create a child zombie process for at least 10 sec duration */
int main(void)
{
    /* os type compliant os id*/
    pid_t pid;

    /* fork creates a child process, copies the stack and heap and text (program code) and a metadata of a parent process (except pid varaible)*/
    pid = fork();

    /* if pid is < 0 there was an error while creating the process */
    if (pid < 0){
        fprintf(stderr ,"could not create the process");
        return 1;
    }
    /* after creation, the child's pid variable is set to 0, in that case we want a zombie process so we return immediately*/
    else if (pid == 0){
        return 0;
    }
    /* if we get pid > 0, that means we are in the parent process, so we wait 10 seconds while the child is a Zombie, and then "collect" the child and return*/
    else if (pid > 0) {
        sleep(10);
        wait(NULL);
        printf("parent process exit");
    }
    return 0;
}
