#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MSG_SIZE 20

int main(int argc, char *argv[])
{
    int fds[2];
    int status;
    pid_t pid;

    char *msg = "Hello World!";
    char buffer[MSG_SIZE];

    if (pipe(fds) == -1){
        printf("pipe() failed\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == 0){
        printf("I'm reader\n");

        if (close(fds[1]) == -1){
            printf("close fds[1] children process failed\n");
            exit(EXIT_FAILURE);
        }

        read(fds[0], buffer, MSG_SIZE);
        printf("The number of character received is: %d\n", (int) strlen(buffer));
    }
    else if (pid > 0){
        printf("I'm writer\n");

        if (close(fds[0]) == -1){
            printf("close fds[0] parent process failed\n");
            exit(EXIT_FAILURE);
        }

        write(fds[1], msg, strlen(msg));

        if (close(fds[1]) == -1){
            printf("close fds[1] parent process failed\n");
            exit(EXIT_FAILURE);
        }

        if (wait(&status) == -1){
            printf("wait() failed\n");
        }
    }
    else {
        printf("fork() failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}