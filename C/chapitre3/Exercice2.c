#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    char *rep_dst = argv[1];
    execlp("cp", "cp", "-r", ".", rep_dst, NULL);
    perror("exec");
    return (1);
}