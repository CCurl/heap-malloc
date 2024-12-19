// hp_malloc - A simple and minimal heap-based memory manager
// Written by Chris Curl.

#ifndef __HP_MALLOC_H__

// Example usage:
//
// Start with hp_init(). Give it the address of the heap and its size.
//
// char heap[HEAP_SZ)];
// hp_init(heap, HEAP_SZ);
// TYPE *pType = (TYPE *)hp_malloc(sizeof(TYPE));
// ... do what ever with pType ...
// hp_free(pType);

extern void hp_init(char *buf, int sz, int num_entries);
extern char *hp_malloc(int sz);
extern char *hp_realloc(char *old_ptr, int new_sz);
extern void hp_free(char *ptr);
extern void hp_gc();
extern void hp_dump();

#endif
