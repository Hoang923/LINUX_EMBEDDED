#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t tid1, tid2;


static void *thr_handle(void *args){
    if (pthread_equal(pthread_self(),tid1)){
        printf("Thread 1: Hello from thread\n");
    }
    else{
        printf("Thread 2: Hello from thread\n");
    }
}

int main(int argc, char const *argv[])
{
    int ret;
    if (ret = pthread_create(&tid1, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    if (ret = pthread_create(&tid2, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    pthread_join(tid1, NULL);
    printf("Thread 1 terminated\n");
    pthread_join(tid2, NULL);
    printf("Thread 2 terminated\n");
    return 0;
}