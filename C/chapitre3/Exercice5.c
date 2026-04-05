#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char *argv[128];
    int count = 0;

    argv[count ++] = "emacs";
    char buff[256];
    while (1){
        printf("Fichier (q pour quitter) :");
        scanf("%255s", buff);
        if ((strcmp(buff, 'q') == 0) || (strcmp(buf, 'Q') ==0)) {
            break;
        }
        arvg[count ++] = strdump(buff);
    }
    argv[count] == NULL;
    execvp("emacs", argv);
    perror("exec");
    return (0);
}