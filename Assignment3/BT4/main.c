#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    int status, rv;

    pid = fork();

    if (pid == 0){
        printf("Child process end after 2 seconds (child PID = %d)\n", getpid());
        sleep(2);
        exit(0);
    }
    else if (pid > 0){
        rv = wait(&status);
        if (rv == -1){
            printf("wait() unsucessful\n");
        }
        if (WIFEXITED(status)){
            printf("Child process terminated nomarlly with the exit code: %d\n", WEXITSTATUS(status));
        }
        else {
            printf("Child process terminated abnormally\n");
        }
    }
    return 0;
}