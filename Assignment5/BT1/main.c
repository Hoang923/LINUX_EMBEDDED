#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int count = 0;

void handle(int sig)
{
    count++;
    printf("\n SIGINT RECEIVED!\n");
    if (count == 3){
        printf("DONE!!\n");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char const *argv[])
{
    if (signal(SIGINT, handle) == SIG_ERR){
        fprintf(stderr, "Cannot handle SIGNIT\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        pause();
    }
}