#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int array[100];

typedef struct{
    int total;
    int count;
} result_t;

void *thr_odd(void *args)
{
    result_t *res = (result_t *)args;

    for (int i = 0; i < 100; i++){
        if (array[i] % 2 == 1){
            res->total += array[i];
            res->count++;
        }
    }
}

void *thr_even(void *args)
{
    result_t *res = (result_t *)args;

    for (int i = 0; i < 100; i++){
        if (array[i] % 2 == 0){
            res->total += array[i];
            res->count++;
        }
    }
}

int main(int argc, char const *argv[])
{
    result_t odd_result = {0,0};
    result_t even_result = {0,0};
    pthread_t odd_thread, even_thread;
    
    srand(time(NULL));
    
    for (int i = 0; i < 100; i++){
        array[i] = rand() % 100 + 1;
    }

    if (pthread_create(&odd_thread, NULL, &thr_odd, &odd_result)){
        printf("create odd thread fail\n");
    }
    if (pthread_create(&even_thread, NULL, &thr_even, &even_result)){
        printf("create even thread fail\n");
    }

    pthread_join(odd_thread, NULL);
    pthread_join(even_thread, NULL);

    printf("Total odd number: %d (n = %d)\n", odd_result.total, odd_result.count);
    printf("Total even number: %d (n = %d)\n", even_result.total, even_result.count);

    return 0;
}