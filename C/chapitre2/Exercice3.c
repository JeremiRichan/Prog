#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int i;
    for (i = 0; i<5; i++){
        pid_t pid = fork();
        if (pid == 0){
            break;
        }
    }
    if(i <5){
        printf("fils %d\n",i + 1);
    }else{
        for (i = 0; i < 5; i++){
            wait(NULL);
        }
    }
    return (0);
}