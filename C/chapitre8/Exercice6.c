#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

pthread_mutex_t mutex_ecriture = PTHREAD_MUTEX_INITIALIZER;
int clients[100];
int nb_clients = 0;

void *gerer_client(void *arg) {
    int sock = *(int *)arg;
    char buf[256];
    int n;
    while ((n = read(sock, buf, sizeof(buf))) > 0) {
        buf[n] = '\0';
        pthread_mutex_lock(&mutex_ecriture);
        int i;
        for (i = 0; i < nb_clients; i++) {
            if (clients[i] != sock) {
                write(clients[i], buf, strlen(buf));
            }
        }
        pthread_mutex_unlock(&mutex_ecriture);
    }
    return NULL;
}

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, 10);
    while (1) {
        int c = accept(sock, NULL, NULL);
        pthread_mutex_lock(&mutex_ecriture);
        clients[nb_clients] = c;
        nb_clients++;
        pthread_mutex_unlock(&mutex_ecriture);
        pthread_t tid;
        pthread_create(&tid, NULL, gerer_client, &clients[nb_clients - 1]);
        pthread_detach(tid);
    }
    close(sock);
    return 0;
}