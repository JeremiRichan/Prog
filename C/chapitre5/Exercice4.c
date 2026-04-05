#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>

pthread_t t_cancel;
void *annule(void *arg) {
    char c;
    while (1) {
        c = getchar();
        if (c == 'A') {
            printf("Annulation\n");
            exit(0);
        }
    }
    return NULL;
}

void *gen(void *arg) {
    int *t = (int *)arg;
    int i;
    for (i = 0; i < t[0]; i++) {
        t[i+1] = rand() % 100;
    }
    return NULL;
}

void *inclus(void *arg) {
    int **mat = (int **)arg;
    int *t1 = mat[0];
    int *t2 = mat[1];
    int n1 = t1[0];
    int n2 = t2[0];
    int i;
    int j;
    for (i = 1; i <= n1; i++) {
        int found = 0;
        for (j = 1; j <= n2; j++) {
            if (t1[i] == t2[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int *r = malloc(sizeof(int));
            *r = 0;
            return r;
        }
    }
    int *r = malloc(sizeof(int));
    *r = 1;
    return r;
}

int main(void) {
    srand(time(NULL));
    int n1 = 3;
    int n2 = 6;
    int *t1 = malloc((n1 + 1) * sizeof(int));
    int *t2 = malloc((n2 + 1) * sizeof(int));
    t1[0] = n1;
    t2[0] = n2;
    pthread_t p1;
    pthread_create(&p1, NULL, gen, t1);
    pthread_t p2;
    pthread_create(&p2, NULL, gen, t2);
    pthread_t pc;
    pthread_create(&pc, NULL, annule, NULL);
    pthread_detach(pc);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    int *mat[] = {t1, t2};
    pthread_t pi;
    pthread_create(&pi, NULL, inclus, mat);
    int *res;
    pthread_join(pi, (void **)&res);
    printf("Inclus: %d\n", *res);
    free(res);
    free(t1);
    free(t2);
    return 0;
}