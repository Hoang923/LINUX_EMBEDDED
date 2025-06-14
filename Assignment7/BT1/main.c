#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char send_buff[] = "hello world";
    char recv_buff[sizeof(send_buff)];
    int num_read;
    int status;
    int fds[2];
    pid_t pid;

    if (pipe(fds) < 0){
        printf("pipe() failed\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == 0){
        printf("I'm reader\n");

        if (close(fds[1]) == -1){
            printf("close fds[1] of children process failed\n");
            exit(EXIT_FAILURE);
        }

        while(1){
            num_read = read(fds[0], recv_buff, sizeof(send_buff));
            if (num_read == -1){
                printf("read() failed\n");
                exit(EXIT_FAILURE);
            }
            else if (num_read == 0){
                printf("pipe end of pipe\n");
                break;
            }
            else{
                printf("Message: %s\n", recv_buff);
            }
        }
    }
    else if (pid > 0){
        printf("I'm writer\n");

        if (close(fds[0]) == -1){
            printf("close fds[0] of parent process failed\n");
            exit(EXIT_FAILURE);
        }

        sleep(2);

        write(fds[1], send_buff, sizeof(send_buff));

        if (close(fds[1]) == -1){
            printf("close fds[1] of parent process failed\n");
            exit(EXIT_FAILURE);
        }

        if (wait(&status) == -1){
            printf("wait() failed\n");
        }
    }
    else{
        printf("fork() failed\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}