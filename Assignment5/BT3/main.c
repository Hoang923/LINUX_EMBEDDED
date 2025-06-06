#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void handle(int sig)
{
    printf("Received signal from parent\n");
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0){
        if (signal(SIGUSR1, handle) == SIG_ERR){
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
        printf("Children process. ID: %d\n", getpid());
        while(1){
            pause();
        }
    }
    else if (pid > 0){
        printf("Parent process. ID children process: %d\n", pid);
        sleep(1);
        for (int i = 0; i < 5; i++){
            kill(pid, SIGUSR1);
            sleep(2);
        }
        kill(pid, SIGTERM);
        if (wait(&status) == -1){
            printf("wait() failed\n");
        }
        printf("DONE!\n");
    }
    else{
        printf("Error\n");
    }
    return 0;
}