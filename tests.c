#include <stdio.h>
#include "hp_malloc.h"

char buf[1000];

int main() {
    hp_init(buf, sizeof(buf));
    char *x1 = hp_malloc(50); printf("x1: %p\n", x1);
    char *x2 = hp_malloc(50); printf("x2: %p\n", x2);
    hp_free(x2);
    char *x3 = hp_malloc(20); printf("x3: %p\n", x3);
    char *x4 = hp_malloc(100); printf("x4: %p\n", x4);
    hp_free(x1);
    hp_free(x3);
    hp_free(x2);
    hp_free(x4);
    char *x5 = hp_malloc(200); printf("x5: %p\n", x5);
    hp_free(x5);
    x5 = hp_malloc(250); printf("x5: %p\n", x5);
    hp_free(0);
    printf("\n");
    return 0;
}
