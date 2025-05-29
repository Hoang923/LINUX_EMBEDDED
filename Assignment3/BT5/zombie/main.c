#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;


    pid = fork();
    if (pid == 0){
        printf("child process ID: %d", getpid());
    }
    else if (pid > 0){
        while(1);
    }
    else {
        printf("error\n");
    }
    return 0;
}