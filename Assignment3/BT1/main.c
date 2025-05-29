#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t child_id;
    int status, rv;

    child_id = fork();
    if (child_id == 0){
        printf("I'm the child process, my PID is %d\n", getpid());
    }
    else if (child_id > 0){
        rv = wait(&status);
        if (rv == -1){
            printf("wait() unsuccessfu\n");
        }

        printf("I'm the parent process, my child PID is %d\n", child_id);
    }
    else{
        printf("Error\n");
    }
    return 0;
}