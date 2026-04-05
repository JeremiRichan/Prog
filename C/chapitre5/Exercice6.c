#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
double tab[100];

void *lisse(void *arg) {
    while (1) {
        pthread_mutex_lock(&m);
        double tmp[100];
        int i;
        for (i = 0; i < 100; i++) {
            tmp[i] = tab[i];
        }
        for (i = 1; i < 99; i++) {
            tab[i] = (tmp[i-1] + tmp[i] + tmp[i+1]) / 3.0;
        }
        pthread_mutex_unlock(&m);
        sleep(1 + rand() % 3);
    }
    return NULL;
}

void *affiche(void *arg) {
    while (1) {
        pthread_mutex_lock(&m);
        int i;
        for (i = 0; i < 100; i++) {
            printf("%.2f ", tab[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&m);
        sleep(4);
    }
    return NULL;
}

int main(void) {
    srand(time(NULL));
    int i;
    for (i = 1; i < 99; i++) {
        tab[i] = rand() % 100;
    }
    tab[0] = 0;
    tab[99] = 0;
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, lisse, NULL);
    pthread_create(&t2, NULL, affiche, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}