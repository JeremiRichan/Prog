#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t s1;
sem_t s2;

void *rendez(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        sleep(2);
        sem_wait(&s2);
        printf("Rendez-vous %d\n", i + 1);
        sem_post(&s1);
    }
    return NULL;
}

void *autre(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        sleep(4 + rand() % 6);
        sem_post(&s2);
        sem_wait(&s1);
    }
    return NULL;
}

int main(void) {
    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 1);
    srand(time(NULL));
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, rendez, NULL);
    pthread_create(&t2, NULL, autre, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&s1);
    sem_destroy(&s2);
    return 0;
}