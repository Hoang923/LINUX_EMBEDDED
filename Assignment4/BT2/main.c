#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREAD 3
#define INCREMENT_PER_THREAD 100000

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int counter = 0;

void *thr_handle(void *args)
{
    pthread_mutex_lock(&lock);
    for (int i = 0; i < INCREMENT_PER_THREAD; i++){
        counter++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t thread[NUM_THREAD];
    for (int i = 0; i < NUM_THREAD; i++){
        if (pthread_create(&thread[i], NULL, thr_handle, NULL)){
            printf("pthread_create fail");
            return -1;
        }
    }
    for (int i = 0; i < NUM_THREAD; i++){
        pthread_join(thread[i], NULL);
    }

    printf("Expected counter: %d\n", NUM_THREAD * INCREMENT_PER_THREAD);
    printf("Actual counter: %d\n", counter);
    
    return 0;
}