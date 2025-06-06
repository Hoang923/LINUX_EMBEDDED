#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define COUNT 10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int data = 0;

void *producer(void *args)
{
    for (int i = 0; i < COUNT; i++){
        pthread_mutex_lock(&lock);
        data = rand() % 10 + 1;
        printf("[Producer] Created data: %d (i = %d)\n", data, i+1);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *args)
{
    for (int i = 0; i < COUNT; i++){
        pthread_mutex_lock(&lock);
        while (1){
            pthread_cond_wait(&cond, &lock);
            printf("[Consumer] Data = %d\n", data);
            break;
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    pthread_t prod_thread, cons_thread;

    if (pthread_create(&cons_thread, NULL, consumer, NULL)){
        printf("create cons_thread fail\n");
    }
    sleep(1);
    if (pthread_create(&prod_thread, NULL, producer, NULL)){
        printf("create prod_thread fail\n");
    }
    
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    printf("DONE\n");

    return 0;
}