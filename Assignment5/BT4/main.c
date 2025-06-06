#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle(int sig)
{
    printf("\n SIGTSTP ignore\n");
}

int main(int argc, char const *argvp[])
{
    if (signal(SIGTSTP, handle) == SIG_ERR){
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }
    while(1){
        pause();
    }

    return 0;
}