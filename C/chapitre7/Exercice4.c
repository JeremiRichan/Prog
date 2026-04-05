#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf env;

void handler(int s) {
    siglongjmp(env, 1);
}

int main(void) {
    signal(SIGSEGV, handler);
    int n;
    scanf("%d", &n);
    int *t = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    while (1) {
        int idx;
        printf("Index: ");
        scanf("%d", &idx);
        if (sigsetjmp(env, 1)) {
            printf("Erreur, resaisir: ");
            continue;
        }
        printf("%d\n", t[idx]);
        break;
    }
    free(t);
    return 0;
}