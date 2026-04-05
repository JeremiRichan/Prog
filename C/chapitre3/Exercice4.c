#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char rep[256];

    while(1){
        printf("Repertoire (q quitter) : ");
        if((strcmp(rep, "q") == 0) || (strcmp(rep, "Q") == 0)){
            break;
        }
        char cmd[521];
        snprintf(cmd, "cp -r . \"%s\"", rep);
        system(cmd);
    }
    return (0);
}