#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void) {
    int n;
    scanf("%d", &n);
    int *t = malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    FILE *f = fopen("tab.bin", "wb");
    fwrite(t, sizeof(int), n, f);
    fclose(f);
    chmod("tab.bin", 0640);
    free(t);
    return 0;
}