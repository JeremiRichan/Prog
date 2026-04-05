#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, 5);
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client = accept(sock, (struct sockaddr *)&client_addr, &client_len);
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, sizeof(ip_str));
    FILE *f = fopen("add_autoris.txt", "r");
    int ok = 0;
    char nom[100];
    char line[256];
    while (fgets(line, sizeof(line), f) != NULL) {
        char ip_file[50];
        char name_file[50];
        if (sscanf(line, "%s %s", ip_file, name_file) == 2) {
            if (strcmp(ip_file, ip_str) == 0) {
                strcpy(nom, name_file);
                ok = 1;
                break;
            }
        }
    }
    fclose(f);
    if (ok) {
        char msg[150];
        sprintf(msg, "Bienvenue %s\n", nom);
        write(client, msg, strlen(msg));
    } else {
        write(client, "Refusé\n", 7);
    }
    close(client);
    close(sock);
    return 0;
}