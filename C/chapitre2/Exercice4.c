#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int fils_id = 0;

int main()
{
    int i;
    for(i =1; i<=5; i++){
        pid_t pid = fork();
        if (pid == 0){
            fils_id = i;
            break;
        }
    }
    if (fils_id >0){
        printf("Je suis le fils %d \n",fils_id);
    }else {
        printf("Je suis le père\n");
        for (i=0; i<5; i++){
            wait(NULL);
        }
    }
    return (0);
}