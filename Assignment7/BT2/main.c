#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MSG_SIZE 100

int main(int argc, char *argv[])
{
    pid_t pid1, pid2;
    int status1, status2;
    int fds1[2];
    int fds2[2];

    char *msg = "Hello";
    char buffer[MSG_SIZE];
    char final_buffer[MSG_SIZE];


    if ((pipe(fds1) == -1) || (pipe(fds2) == -1)){
        printf("pipe() failed\n");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 < 0){
        printf("fork() pid1 failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid1 == 0){
        printf("I'm children 1\n");

        if ((close(fds1[1]) == -1) || (close(fds2[0]) == -1)){
            printf("close() fds children1 failed\n");
            exit(EXIT_FAILURE);
        }

        read(fds1[0], buffer, MSG_SIZE);
        strcat(buffer, " World!!!\n");
        write(fds2[1], buffer, sizeof(buffer));

        if (close(fds2[1]) == -1){
            printf("close() fds2[1] children1 failed\n");
            exit(EXIT_FAILURE);
        }
        
        exit(EXIT_SUCCESS);
    }

    pid2 = fork();
    if (pid2 < 0){
        printf("fork() pid2 failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid2 == 0){
        printf("I'm children 2\n");

        if ((close(fds1[1]) == -1) || (close(fds2[1]) == -1) || (close(fds1[0]) == -1)){
            printf("close() fds children2 failed\n");
            exit(EXIT_FAILURE);
        }

        read(fds2[0], final_buffer, MSG_SIZE);
        printf("Child 2 received: %s", final_buffer);

        exit(EXIT_SUCCESS);
    }

    printf("I'm parent\n");
    
    if ((close(fds1[0]) == -1) || (close(fds2[0]) == -1) || (close(fds2[1])) == -1){
        printf("close() fds parent failed\n");
        exit(EXIT_FAILURE);
    }

    write(fds1[1], msg, strlen(msg));
    if (close(fds1[1]) == -1){
            printf("close() fds1[1] parent failed\n");
            exit(EXIT_FAILURE);
        }

    if ((wait(&status1) == -1) || (wait(&status2) == 1)){
        printf("wait() failed\n");
    }

    return 0;
}