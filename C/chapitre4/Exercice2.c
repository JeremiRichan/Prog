#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int tube[2];
    pipe(tube);
    pid_t pid = fork();
    if (pid == 0) {
        dup2(tube[0], STDIN_FILENO);
        close(tube[0]);
        close(tube[1]);
        char mot[256];
        scanf("%s", mot);
        _exit(0);
    }
    close(tube[0]);
    FILE *f = fopen("fichier.txt", "r");
    char buf[256];
    while (fscanf(f, "%s", buf) != EOF) {
        dprintf(tube[1], "%s ", buf);
    }
    fclose(f);
    close(tube[1]);
    wait(NULL);
    return 0;
}