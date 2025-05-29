#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    if (argc != 2){
        printf("%s 1/2", argv[0]);
        return 1;
    }

    char mode = argv[1][0];

    if ((mode != '1')&&(mode != '2')){
        printf("%s 1/2", argv[0]);
        return 1;
    }

    pid_t pid;
    int status, rv;

    pid = fork();
    if (pid == 0){
        if (mode == '1'){
            execlp("/usr/bin/ls", "ls", NULL);
            printf("exec unsucessful\n");
        }
        else{
            execlp("/usr/bin/date", "date", NULL);
            printf("exec unsucessful\n");
        }
    }
    else if (pid > 0){
        rv = wait(&status);
        if (rv == -1){
            printf("wait() unsucessfull\n");
        }
        printf("Parent process\n");
    }
    else{
        printf("Error\n");
    }
    return 0;
}