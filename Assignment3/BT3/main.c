#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handle(int sig){
    printf("Child process received SIGUSR1, signal number: %d\n", sig);
    exit(0);
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status,rv;

    pid = fork();
    if (pid == 0){
        signal(SIGUSR1, handle);
        printf("Child process\n");
        pause();
    }
    else if (pid > 0){
        sleep(2); 
        printf("Parent process send signal\n");
        kill(pid,SIGUSR1);
        rv = wait(&status);
        if (rv == -1){
            printf("wait() unsucessful\n");
        }
    }
    else{
        printf("Error\n");
    }
    return 0;
}