#include <stdio.h>
#include <pthread.h>

void *affiche(void *arg) {
    int *t = (int *)arg;
    int i;
    for (i = 0; i < 5; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");
    return NULL;
}

int main(void) {
    int tab[] = {1, 2, 3, 4, 5};
    pthread_t th;
    pthread_create(&th, NULL, affiche, tab);
    pthread_join(th, NULL);
    return 0;
}