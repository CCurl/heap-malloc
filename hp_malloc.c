// hp_malloc - A minimal heap-based memory manager
// Written by Chris Curl, 2023-07-09

#include "hp_malloc.h"

#define NULL 0

typedef struct hp_alloc_t { 
    struct hp_alloc_t *prev, *next;
    int sz, isFree;
    char *ptr; 
} HP_ALLOC_T;

static HP_ALLOC_T *start, *end;
static char *heap, *hhere, *heap_end;
static int heap_sz;

void hp_init(char *buf, int sz) {
    heap = hhere = buf;
    heap_sz = sz;
    heap_end = heap + heap_sz;
    start = end = NULL;
}

static char *hp_get(sz) {
    while (((long)hhere & 0x04) != 0) { ++hhere; }
    if (hhere+sz >= heap_end) { return NULL; }
    char *ret = hhere;
    hhere += sz;
    return ret;
}

static char *hp_reuse(int sz) {
    HP_ALLOC_T *x = start;
    while (x) {
        if (x->isFree && (sz <= x->sz)) {
            x->isFree = 0;
            return x->ptr;
        }
        x = x->next;
    }
    return NULL;
}

char *hp_malloc(int sz) {
    char *ptr = hp_reuse(sz);
    if (ptr) { return ptr; }
    HP_ALLOC_T *x = (HP_ALLOC_T *)hp_get(sizeof(HP_ALLOC_T));
    if (!x) { return NULL; }
    ptr = hp_get(sz);
    if (!ptr) { hhere -= sizeof(HP_ALLOC_T); return NULL; }
    x->prev = end;
    x->next = NULL;
    x->sz = sz;
    x->ptr = ptr;
    x->isFree = 0;
    if (!start) { start = x; }
    if (end) { end->next = x; }
    end = x;
    return ptr;
}

// A simple "garbage collector"
// Cull the "end" entry until it is not free
static void hp_gc() {
    while (end && end->isFree) {
        hhere = (char *)end;
        end = end->prev;
    }
    if (end == NULL) { start = NULL; }
    else { end->next = NULL; }
}

void hp_free(char *ptr) {
    HP_ALLOC_T *x = start;
    while (x && (ptr >= x->ptr)) {
        if (x->ptr == ptr) { x->isFree = 1; }
        x = x->next;
    }
    hp_gc();
}
