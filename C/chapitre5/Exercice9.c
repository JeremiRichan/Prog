#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t plein;
sem_t vide;
unsigned char buf;

void *emetteur(void *arg) {
    while (1) {
        buf = rand() % 256;
        sem_post(&plein);
        sem_wait(&vide);
        sleep(1 + rand() % 3);
    }
    return NULL;
}

void *recepteur(void *arg) {
    while (1) {
        sem_wait(&plein);
        printf("Lu: %d\n", buf);
        sem_post(&vide);
        sleep(1 + rand() % 3);
    }
    return NULL;
}

int main(void) {
    sem_init(&plein, 0, 0);
    sem_init(&vide, 0, 1);
    srand(time(NULL));
    pthread_t e;
    pthread_t r;
    pthread_create(&e, NULL, emetteur, NULL);
    pthread_create(&r, NULL, recepteur, NULL);
    pthread_join(e, NULL);
    pthread_join(r, NULL);
    sem_destroy(&plein);
    sem_destroy(&vide);
    return 0;
}