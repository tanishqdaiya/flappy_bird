#pragma once
#include <stddef.h>

typedef struct arena_s {
    char *data;
    size_t offset;
    size_t size;
} arena_t;

void *M_Alloc(arena_t *a, size_t n);
void *M_StrDup(arena_t *a, const char *s);
void M_Free(arena_t *a); /* does not free actual memory */
