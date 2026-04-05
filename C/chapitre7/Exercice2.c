#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int s) {
    FILE *f = fopen("/tmp/entier.txt", "r");
    int v;
    fscanf(f, "%d", &v);
    fclose(f);
    printf("Lu: %d\n", v);
}

int main(void) {
    pid_t pid = fork();
    if (pid == 0) {
        int n;
        printf("Entier: ");
        scanf("%d", &n);
        FILE *f = fopen("/tmp/entier.txt", "w");
        fprintf(f, "%d", n);
        fclose(f);
        kill(getppid(), SIGUSR1);
        _exit(0);
    }
    signal(SIGUSR1, handler);
    pause();
    wait(NULL);
    return 0;
}