#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0){
        printf("Je sui le fils\n");
    }
    else if (pid > 0){
        wait(NULL);
        printf("Je suis le père\n");
    }
    return (0);
}