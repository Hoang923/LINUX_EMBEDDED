#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int count = 0;

void handle_alarm(int sig)
{
    count++;
    printf("Timer: %d seconds\n", count);
    if (count == 10){
        printf("Done!\n");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char const *argvp[])
{
    if (signal(SIGALRM, handle_alarm) == SIG_ERR){
        fprintf(stderr, "ERROR\n");
        exit(EXIT_FAILURE);
    }
    
    while(1){
        alarm(1);
        pause();
    }
}