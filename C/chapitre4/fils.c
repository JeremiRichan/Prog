#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int desc = atoi(argv[1]);
    char buf[256];
    read(desc, buf, sizeof(buf));
    printf("%s", buf);
    return 0;
}