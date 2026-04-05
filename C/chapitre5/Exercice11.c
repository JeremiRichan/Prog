#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t m_lect = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m_ecrit = PTHREAD_MUTEX_INITIALIZER;
int lecteurs = 0;
char db[15];

void *lecteur(void *arg) {
    while (1) {
        pthread_mutex_lock(&m_lect);
        lecteurs++;
        if (lecteurs == 1) {
            pthread_mutex_lock(&m_ecrit);
        }
        pthread_mutex_unlock(&m_lect);
        int idx = rand() % 15;
        printf("Lit [%d]=%d\n", idx, db[idx]);
        sleep(1 + rand() % 3);
        pthread_mutex_lock(&m_lect);
        lecteurs--;
        if (lecteurs == 0) {
            pthread_mutex_unlock(&m_ecrit);
        }
        pthread_mutex_unlock(&m_lect);
        sleep(1 + rand() % 3);
    }
    return NULL;
}

void *redacteur(void *arg) {
    while (1) {
        pthread_mutex_lock(&m_ecrit);
        int idx = rand() % 15;
        db[idx] = rand() % 100;
        printf("Ecrit [%d]=%d\n", idx, db[idx]);
        pthread_mutex_unlock(&m_ecrit);
        sleep(1 + rand() % 10);
    }
    return NULL;
}

int main(void) {
    int L;
    int R;
    scanf("%d%d", &L, &R);
    srand(time(NULL));
    pthread_t t[L + R];
    int i;
    for (i = 0; i < L; i++) {
        pthread_create(&t[i], NULL, lecteur, NULL);
    }
    for (i = 0; i < R; i++) {
        pthread_create(&t[L + i], NULL, redacteur, NULL);
    }
    for (i = 0; i < L + R; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}