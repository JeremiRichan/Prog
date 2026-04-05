#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char fichier[256];

    printf("nom du fichier : ");
    scanf("%255s", fichier);
    execlp("/usr/bin/emacs", "emacs", fichier, NULL);
    perror("exec")
    return (1);
}