#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *gen(void *arg) {
    int *t = malloc(10 * sizeof(int));
    int i;
    for (i = 0; i < 10; i++) {
        t[i] = rand() % 100;
    }
    return t;
}

int main(void) {
    srand(time(NULL));
    pthread_t th;
    pthread_create(&th, NULL, gen, NULL);
    int *res;
    pthread_join(th, (void **)&res);
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
    free(res);
    return 0;
}