#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

int main(int argc, char **argv) {
    int i;
    for (i = 1; i < argc; i++) {
        DIR *d = opendir(argv[i]);
        if (d == NULL) continue;
        struct dirent *e;
        while ((e = readdir(d)) != NULL) {
            char p[1024];
            snprintf(p, sizeof(p), "%s/%s", argv[i], e->d_name);
            struct stat st;
            if (stat(p, &st) == 0 && S_ISREG(st.st_mode) && st.st_size > 1048576) {
                struct passwd *pw = getpwuid(st.st_uid);
                printf("%s %s\n", p, pw ? pw->pw_name : "?");
            }
        }
        closedir(d);
    }
    return 0;
}