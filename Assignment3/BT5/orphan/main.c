#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;

    pid = fork();
    if (pid == 0){
        sleep(5);
        printf("my parent PID: %d\n", getppid());
    }
    else if (pid > 0){
        printf("parent process terminated (PID = %d)\n", getpid());
    }
    else {
        printf("error\n");
    }
    return 0;
}