#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int tube[2];
    pipe(tube);
    pid_t pid = fork();
    if (pid == 0) {
        char desc[16];
        sprintf(desc, "%d", tube[0]);
        execl("./fils", "./fils", desc, NULL);
        _exit(1);
    }
    close(tube[0]);
    write(tube[1], "message\n", 8);
    close(tube[1]);
    wait(NULL);
    return 0;
}