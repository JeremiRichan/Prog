#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
double u = 1.0;
int iter = 0;

void *t1(void *arg) {
    while (1) {
        pthread_mutex_lock(&m);
        u = 0.25 * (u - 1) * (u - 1);
        iter++;
        printf("T1 u=%.4f\n", u);
        pthread_mutex_unlock(&m);
        sleep(1 + rand() % 5);
    }
    return NULL;
}

void *t2(void *arg) {
    while (1) {
        pthread_mutex_lock(&m);
        u = (1.0 / 6.0) * (u - 2) * (u - 2);
        iter++;
        printf("T2 u=%.4f\n", u);
        pthread_mutex_unlock(&m);
        sleep(1 + rand() % 5);
    }
    return NULL;
}

int main(void) {
    srand(time(NULL));
    pthread_t th1;
    pthread_t th2;
    pthread_create(&th1, NULL, t1, NULL);
    pthread_create(&th2, NULL, t2, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    return 0;
}