#include <stdio.h>
#include "heap.h"

int main() {
    char *x1 = hAlloc(10); printf("x1: %p\n", x1);
    char *x2 = hAlloc(20); printf("x2: %p\n", x2);
    hFree(x2);
    char *x3 = hAlloc(30); printf("x3: %p\n", x3);
    char *x4 = hAlloc(40); printf("x4: %p\n", x4);
    hFree(x1);
    hFree(x3);
    // hFree(x4);
    char *x5 = hAlloc(50); printf("x5: %p\n", x5);
    hFree(0);
    // hFree(x5);
    // hFree(x5);
    printf("\n");
    x1 = hAlloc(10);
    for (int i=0; i<9; i++) { x1[i] = 'A'+i; } x1[9]=0;
    printf("[%s]=?[%s]\n", x1, x2);
    // hFree(x2);
    hDump(1, NULL);
    return 0;
}
