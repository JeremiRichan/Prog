#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int *tab;
    int n;
    int x;
} TypeTableau;

void *init(void *arg) {
    TypeTableau *T = (TypeTableau *)arg;
    int i;
    for (i = 0; i < T->n; i++) {
        T->tab[i] = rand() % 100;
    }
    return NULL;
}

void *cherche(void *arg) {
    TypeTableau *T = (TypeTableau *)arg;
    int i;
    int trouve = 0;
    for (i = 0; i < T->n; i++) {
        if (T->tab[i] == T->x) {
            trouve = 1;
            break;
        }
    }
    int *res = malloc(sizeof(int));
    *res = trouve;
    return res;
}

int main(void) {
    srand(time(NULL));
    TypeTableau T;
    T.n = 5;
    T.tab = malloc(T.n * sizeof(int));
    printf("x: ");
    scanf("%d", &T.x);
    pthread_t t1;
    pthread_create(&t1, NULL, init, &T);
    pthread_join(t1, NULL);
    pthread_t t2;
    pthread_create(&t2, NULL, cherche, &T);
    int *res;
    pthread_join(t2, (void **)&res);
    printf("%d\n", *res);
    free(res);
    free(T.tab);
    return 0;
}