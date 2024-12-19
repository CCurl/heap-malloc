#include <stdio.h>
#include "hp_malloc.h"

char buf[1000];

int main() {
    hp_init(buf, sizeof(buf), 10);
    char *x1 = hp_malloc(10); printf("x1: %p\n", x1);
    char *x2 = hp_malloc(20); printf("x2: %p\n", x2);
    hp_free(x2);
    char *x3 = hp_malloc(30); printf("x3: %p\n", x3);
    char *x4 = hp_malloc(40); printf("x4: %p\n", x4);
    hp_free(x1);
    hp_free(x3);
    // hp_free(x4);
    char *x5 = hp_malloc(50); printf("x5: %p\n", x5);
    x5 = hp_realloc(x5, 55); printf("x5: %p\n", x5);
    hp_free(0);
    hp_free(x5);
    printf("\n");
    x1 = hp_malloc(10);
    for (int i=0; i<9; i++) { x1[i] = 'A'+i; } x1[9]=0;
    x2 = hp_realloc(x1, 20);
    printf("[%s]=?[%s]\n", x1, x2);
    // hp_free(x2);
    hp_dump();
    return 0;
}
