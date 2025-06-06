#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>

void handle_sigint(int sig)
{
    printf("\nSIGINT received\n");
}

void handle_sigterm(int sig)
{
    printf("EXIT THE PROGRAM\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char const argv[])
{
    if (signal(SIGINT, handle_sigint) == SIG_ERR){
        fprintf(stderr, "cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGTERM, handle_sigterm) == SIG_ERR){
        fprintf(stderr, "cannot handle SIGTERM\n");
        exit(EXIT_FAILURE);
    }

    printf("My ID: %d\nType somthing...\n", getpid());

    char buf[256];
    fd_set readfds;

    while(1){
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        select(STDIN_FILENO + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &readfds)){
            ssize_t len = read(STDIN_FILENO, buf, sizeof(buf)-1);
            if (len > 0){
                buf[len] = '\0';
            }
            printf("You typed: %s", buf);
        }
    }
}