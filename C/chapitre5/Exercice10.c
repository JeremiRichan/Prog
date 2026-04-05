#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define N 10
sem_t mutex;
sem_t vide;
sem_t plein;
int buffer[N];
int in = 0;
int out = 0;

void *prod(void *arg) {
    while (1) {
        int item = rand() % 256;
        sem_wait(&vide);
        sem_wait(&mutex);
        buffer[in] = item;
        in = (in + 1) % N;
        sem_post(&mutex);
        sem_post(&plein);
        sleep(1 + rand() % 3);
    }
    return NULL;
}

void *cons(void *arg) {
    while (1) {
        sem_wait(&plein);
        sem_wait(&mutex);
        int item = buffer[out];
        out = (out + 1) % N;
        printf("Consommé: %d\n", item);
        sem_post(&mutex);
        sem_post(&vide);
        sleep(1 + rand() % 3);
    }
    return NULL;
}

int main(void) {
    int P;
    int M;
    scanf("%d%d", &P, &M);
    sem_init(&mutex, 0, 1);
    sem_init(&vide, 0, N);
    sem_init(&plein, 0, 0);
    srand(time(NULL));
    pthread_t t[P + M];
    int i;
    for (i = 0; i < P; i++) {
        pthread_create(&t[i], NULL, prod, NULL);
    }
    for (i = 0; i < M; i++) {
        pthread_create(&t[P + i], NULL, cons, NULL);
    }
    for (i = 0; i < P + M; i++) {
        pthread_join(t[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&vide);
    sem_destroy(&plein);
    return 0;
}