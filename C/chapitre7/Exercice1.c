#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid == 0) {
        while (1) { }
    }
    char k;
    while (scanf(" %c", &k) == 1) {
        if (k == 's') kill(pid, SIGSTOP);
        else if (k == 'r') kill(pid, SIGCONT);
        else if (k == 'q') {
            kill(pid, SIGTERM);
            break;
        }
    }
    wait(NULL);
    return 0;
}