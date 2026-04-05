#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int tube[2];
    pipe(tube);
    pid_t pid = fork();
    if (pid == 0) {
        close(tube[0]);
        char mot[256];
        printf("Mot: ");
        scanf("%s", mot);
        write(tube[1], mot, strlen(mot) + 1);
        close(tube[1]);
        _exit(0);
    }
    close(tube[1]);
    char mot[256];
    read(tube[0], mot, sizeof(mot));
    FILE *f = fopen("fichier.txt", "r");
    char buf[256];
    int trouve = 0;
    while (fscanf(f, "%s", buf) != EOF) {
        if (strcmp(buf, mot) == 0) {
            trouve = 1;
        }
    }
    fclose(f);
    printf("%d\n", trouve);
    wait(NULL);
    return 0;
}