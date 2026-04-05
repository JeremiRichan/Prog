#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int s) {
    printf("Fils %d tué\n", getpid());
    _exit(0);
}

pid_t fils[5];

int main(void) {
    int i;
    for (i = 0; i < 5; i++) {
        fils[i] = fork();
        if (fils[i] == 0) {
            signal(SIGTERM, handler);
            while (1) { }
        }
    }
    char cmd;
    int num;
    while (scanf(" %c %d", &cmd, &num) == 2) {
        if (cmd == 's') kill(fils[num], SIGSTOP);
        else if (cmd == 'r') kill(fils[num], SIGCONT);
        else if (cmd == 't') kill(fils[num], SIGTERM);
    }
    return 0;
}