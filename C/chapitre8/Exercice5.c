#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void *relais(void *arg) {
    int c1 = ((int*)arg)[0];
    int c2 = ((int*)arg)[1];
    char buf[256];
    while (1) {
        int n = read(c1, buf, sizeof(buf));
        if (n <= 0) break;
        buf[n] = '\0';
        char msg[300];
        sprintf(msg, "L'autre client dit: %s\n", buf);
        write(c2, msg, strlen(msg));
    }
    return NULL;
}

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, 2);
    int c1 = accept(sock, NULL, NULL);
    int c2 = accept(sock, NULL, NULL);
    int fds1[2];
    fds1[0] = c1;
    fds1[1] = c2;
    pthread_t t1;
    pthread_create(&t1, NULL, relais, fds1);
    int fds2[2];
    fds2[0] = c2;
    fds2[1] = c1;
    pthread_t t2;
    pthread_create(&t2, NULL, relais, fds2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    close(c1);
    close(c2);
    close(sock);
    return 0;
}