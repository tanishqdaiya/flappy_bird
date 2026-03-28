#include <string.h>
#include "m_memory.h"

void *M_Alloc(arena_t *a, size_t n)
{
    void *m;

    n = (n + 7) & ~7; /* alignment logic */
    if (a->offset + n > a->size)
        return NULL;
    m = a->data + a->offset;
    a->offset += n;
    return m;
}

void *M_StrDup(arena_t *a, const char *s)
{
    char *p;
    if ((p = M_Alloc(a, strlen(s) + 1)) != NULL)
        strcpy(p, s);
    return p;
}

void M_Free(arena_t *a)
{
    a->offset = 0;
}
