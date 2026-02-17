#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *a_func(void *arg) {
    long j;
    for (j = 0; j < 100000000; j++) {
        pthread_mutex_lock(&lock1);
        pthread_mutex_lock(&lock2);
        printf("A");
        pthread_mutex_unlock(&lock2);
        pthread_mutex_unlock(&lock1);
    }
    return NULL;
}

void *b_func(void *arg) {
    long j;
    for (j = 0; j < 100000000; j++) {
        pthread_mutex_lock(&lock2);
        pthread_mutex_lock(&lock1);
        printf("B");
        pthread_mutex_unlock(&lock1);
        pthread_mutex_unlock(&lock2);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t a, b;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);
    pthread_create(&a, NULL, a_func, NULL);
    pthread_create(&b, NULL, b_func, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    printf("End!\n");
}