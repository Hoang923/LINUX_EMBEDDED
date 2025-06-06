#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4 

int array[ARRAY_SIZE];
int total = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
    int start;
    int end;
}thread_size_t;

void *thr_handle(void *args)
{
    int local_total = 0;
    thread_size_t size = *(thread_size_t *)args;
    free(args);
    for (int i = size.start; i <= size.end; i++){
        local_total += array[i];
    }
    pthread_mutex_lock(&lock);
    total += local_total;
    pthread_mutex_unlock(&lock);

    printf("Total: %d (array[%d] -> array[%d]\n", total, size.start, size.end);
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < ARRAY_SIZE; i++){
        array[i] = 1;
    }

    pthread_t threads[NUM_THREADS];
    int segment = ARRAY_SIZE / NUM_THREADS;

    

    for (int i = 0; i < NUM_THREADS; i++){
        thread_size_t *size = malloc(sizeof(thread_size_t));
        size->start = i * segment;
        size->end = (i == NUM_THREADS - 1) ? ARRAY_SIZE - 1 : ((i + 1) * segment) - 1 ; 
        
        if (pthread_create(&threads[i], NULL, thr_handle, size)){
            printf("Error\n");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Successful!! Total: %d\n", total);
}