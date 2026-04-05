#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int compt = 0;
int limite;

void *inc(void *arg) {
    while (1) {
        pthread_mutex_lock(&m);
        compt++;
        int fin = (compt >= limite);
        pthread_mutex_unlock(&m);
        if (fin) break;
        sleep(1 + rand() % 5);
    }
    return NULL;
}

void *aff(void *arg) {
    while (1) {
        pthread_mutex_lock(&m);
        int val = compt;
        int fin = (compt >= limite);
        pthread_mutex_unlock(&m);
        if (fin) break;
        printf("%d\n", val);
        sleep(2);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    limite = atoi(argv[1]);
    srand(time(NULL));
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, inc, NULL);
    pthread_create(&t2, NULL, aff, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}