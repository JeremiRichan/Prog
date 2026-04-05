#include <stdio.h>

int main(void) {
    printf("a) %lld\n", 2LL * 2 * 1000 * 60 * 1024);
    printf("b) %lld\n", ((2LL * 1000 * 60 + 350 * 60 + 45) * 1024 + 300));
    long long o = 78000000;
    long long sec = o / 1024;
    printf("c) secteur %lld, cylindre %lld, face %lld\n", sec % 60, (sec / 60) % 1000, (sec / 60000) % 2);
    return 0;
}