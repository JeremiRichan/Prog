#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t p1;
    pid_t p2;

    p1 = fork();
    if (p1 == 0){
        printf("Je suis le fils 1\n")
        return (0);
    }
    p2 = fork();
    if (p2 == 0){
        printf("Je suis le fils 2\n");
        return (0);
    }
    wait(NULL);
    wait(NULL);
    printf("Je suis le père\n");
    return (0);
}