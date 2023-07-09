// hp_malloc - A minimal heap-based memory manager
// Written by Chris Curl, 2023-07-09

#include "hp_malloc.h"

#define NULL 0

typedef struct heap_t { 
    struct heap_t *prev, *next;
    int sz, isFree;
    char *ptr; 
} HEAP_T;

static HEAP_T *start, *end;
static char *heap, *hh, *h_end;
static int heap_sz;

void hp_init(char *buf, int sz) {
	heap = hh = buf;
	heap_sz = sz;
    h_end = heap + heap_sz;
	start = end = NULL;
}

static char *hp_get(sz) {
	if (hh+sz >= h_end) { return NULL; }
	char *ret = hh;
	hh += sz;
	return ret;
}

static char *hp_reuse(int sz) {
    HEAP_T *x = start;
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
    while (sz % 4) { ++sz; }
    HEAP_T *x = (HEAP_T *)hp_get(sizeof(HEAP_T));
    if (!x) { return NULL; }
    ptr = hp_get(sz);
    if (!ptr) { hh -= sizeof(HEAP_T); return NULL; }
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
        hh = (char *)end;
        end = end->prev;
    }
    if (end == NULL) { start = NULL; }
    else { end->next = NULL; }
}

void hp_free(char *ptr) {
    HEAP_T *x = start;
    while (x && (ptr >= x->ptr)) {
        if (x->ptr == ptr) { x->isFree = 1; }
        x = x->next;
    }
    hp_gc();
}
