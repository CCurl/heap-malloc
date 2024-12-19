// hp_malloc - A simple and minimal heap-based memory manager
// Written by Chris Curl,

#include <stdio.h>
#include "hp_malloc.h"

typedef struct hp_alloc_t { 
    int sz;
    char isFree, *ptr; 
} HP_ALLOC_T;

static HP_ALLOC_T *heap;
static char *hhere, *heap_end;
static int heap_sz;
static int max_entry, last;

void hp_init(char *buf, int sz, int num_entries) {
    heap = (HP_ALLOC_T*)buf;
    heap_sz = sz;
    heap_end = buf + heap_sz;
    max_entry = num_entries-1;
    for (int i=0; i<=max_entry; i++) {
        heap[i].sz = 0;
        heap[i].isFree = 1;
        heap[i].ptr = 0;
    }
    hhere = (char*)&heap[num_entries];
    last = -1;
}

static char *hp_reuse(int sz) {
    HP_ALLOC_T *p = &heap[0];
    for (int i=0; i<=last; i++) {
        if (p->isFree && (sz <= p->sz)) {
            p->isFree = 0;
            return p->ptr;
        }
        p++;
    }
    return 0;
}

char *hp_malloc(int sz) {
    char *ptr = hp_reuse(sz);
    if (ptr) { return ptr; }
    if (heap_end < (hhere + sz)) { return 0; }
    if (max_entry <= last) { return 0; }
    HP_ALLOC_T *p = &heap[++last];
    p->sz = sz;
    p->ptr = hhere;
    p->isFree = 0;
    hhere += sz;
    return p->ptr;
}

char *hp_realloc(char *old_ptr, int new_sz) {
    int old_sz = 0;
    for (int i=0; i<=last; i++) {
        if (heap[i].ptr == old_ptr) { old_sz = heap[i].sz; break; }
    }
    hp_free(old_ptr);
    char *new_ptr = hp_malloc(new_sz);
    if (new_ptr && (new_ptr != old_ptr)) {
        for (int i=0; i<old_sz; i++) { new_ptr[i] = old_ptr[i]; }
    }
    return new_ptr;
}

// A simple "garbage collector"
// Cull the last entry until it is not free
void hp_gc() {
    while ((0 <= last) && heap[last].isFree) {
        hhere = heap[last].ptr;
        heap[last].isFree = 1;
        heap[last].sz = 0;
        heap[last].ptr = 0;
        --last;
    }
}

void hp_free(char *ptr) {
    for (int i=0; i<=last; i++) {
        if (heap[i].ptr == ptr) {
            heap[i].isFree = 1;
            hp_gc();
            break;
        }
    }
}

void hp_dump() {
    if (last < 0) { printf("all free\n"); }
    for (int i=0; i<=last; i++) {
        HP_ALLOC_T *p=&heap[i];
        printf("%d: free=%d, sz=%d, ptr=%p\n", 
            i, p->isFree, p->sz, p->ptr);
    }
}
