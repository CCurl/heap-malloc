// hp_malloc - A heap-based memory manager
// Written by Chris Curl, 2023-07-09

#ifndef __HP_MALLOC_H__

extern void hp_init(char *buf, int sz);
extern char *hp_malloc(int sz);
extern void hp_free(char *ptr);
extern char *hp_get(int sz);

#endif
