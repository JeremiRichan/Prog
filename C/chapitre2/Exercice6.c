#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int n;
    int k;
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    char fichier[256];
    sprintf(fichier, "/tmp/coef_%d_%d.txt", n, k);
    if (k == 0 || k == n) {
        FILE *f;
        f = fopen(fichier, "w");
        fprintf(f, "1");
        fclose(f);
        exit(0);
    }
    pid_t pid1;
    pid_t pid2;
    pid1 = fork();
    if (pid1 == 0) {
        char n1[16];
        sprintf(n1, "%d", n - 1);
        char k1[16];
        sprintf(k1, "%d", k);
        execl(argv[0], argv[0], n1, k1, NULL);
        exit(1);
    }
    pid2 = fork();
    if (pid2 == 0) {
        char n2[16];
        sprintf(n2, "%d", n - 1);
        char k2[16];
        sprintf(k2, "%d", k - 1);
        execl(argv[0], argv[0], n2, k2, NULL);
        exit(1);
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    char f1[256];
    char f2[256];
    sprintf(f1, "/tmp/coef_%d_%d.txt", n - 1, k);
    sprintf(f2, "/tmp/coef_%d_%d.txt", n - 1, k - 1);
    FILE *fp1;
    FILE *fp2;
    fp1 = fopen(f1, "r");
    fp2 = fopen(f2, "r");
    int v1;
    int v2;
    fscanf(fp1, "%d", &v1);
    fscanf(fp2, "%d", &v2);
    fclose(fp1);
    fclose(fp2);
    FILE *f;
    f = fopen(fichier, "w");
    fprintf(f, "%d", v1 + v2);
    fclose(f);
    return 0;
}