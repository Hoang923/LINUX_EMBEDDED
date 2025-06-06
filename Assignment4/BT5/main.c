#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int data = 0; 
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;

void *reader(void *args)
{
    int id = *(int *)args;
    free(args);

    pthread_rwlock_rdlock(&lock);
    printf("Reader %d read: data = %d\n", id, data);
    pthread_rwlock_unlock(&lock);

    return NULL;
}

void *writer(void *args)
{
    int id = *(int *)args;
    free(args);

    pthread_rwlock_wrlock(&lock);
    data++;
    printf("Write %d write: data = %d\n", id, data);
    pthread_rwlock_unlock(&lock);

    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++){
        int *id = malloc(sizeof(int));
        *id = i + 1;
        if (pthread_create(&readers[i], NULL, reader, id)){
            printf("create thread reader %d fail\n", *id);
        }
    }

    for (int i = 0; i < NUM_WRITERS; i++){
        int *id = malloc(sizeof(int));
        *id = i + 1;
        if(pthread_create(&writers[i], NULL, writer, id)){
            printf("create thread writer %d fail\n", *id);
        }
    }

    for (int i = 0; i < NUM_READERS; i++){
        pthread_join(readers[i], NULL);
    }
    
    for (int i = 0; i < NUM_WRITERS; i++){
        pthread_join(writers[i], NULL);
    }

    return 0;
}