#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    time_t debut;
    time_t fin;
    time(&debut);

    srand(time(NULL));
    pid_t p1 = fork();
    pid_t p2 = fork();

    if(p1 == 0){
        sleep(rand() % 10 + 1);
        _exit(0);
    }
    if (p2 == 0){
        sleep(rand() % 10 + 1);
        _exit(0);
    }
    wait(NULL);
    wait(NULL);
    time(&fin);
    printf("La durée total %ld secondes", fin - debut);
    return (0);
}