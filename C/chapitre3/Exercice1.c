#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int a, b, somme;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    somme = a + b;

    printf("%d\n", somme);
    return (0);
}