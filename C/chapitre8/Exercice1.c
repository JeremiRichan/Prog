#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

typedef struct {
    char nom[50];
    float prix;
} Produit;

Produit base[100];
int n = 0;

void charger_base() {
    FILE *f = fopen("base.txt", "r");
    while (fscanf(f, "%s %f", base[n].nom, &base[n].prix) != EOF) {
        n++;
    }
    fclose(f);
}

int main(void) {
    charger_base();
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    listen(sock, 5);
    while (1) {
        int client = accept(sock, NULL, NULL);
        float total = 0;
        char buf[256];
        while (read(client, buf, sizeof(buf)) > 0) {
            char prod[50];
            int qty;
            sscanf(buf, "%s %d", prod, &qty);
            int i;
            for (i = 0; i < n; i++) {
                if (strcmp(base[i].nom, prod) == 0) {
                    total += base[i].prix * qty;
                }
            }
        }
        char resp[100];
        sprintf(resp, "Total: %.2f\n", total);
        write(client, resp, strlen(resp));
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char filename[100];
        strftime(filename, sizeof(filename), "cmd_%Y%m%d_%H%M%S.txt", t);
        FILE *f = fopen(filename, "w");
        fprintf(f, "Commande\nTotal: %.2f\n", total);
        fclose(f);
        close(client);
    }
    return 0;
}