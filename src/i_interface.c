#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "i_interface.h"
#include "u_utils.h"
#include "m_memory.h"

#define HASHSIZE 101
#define MAXLINE 1024

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_ID,
    TOKEN_EQ,
} token_t;

static arena_t *g_configarena;
static struct nlist *hashtab[HASHSIZE];
static char *cursor;

void I_ConfigInit(arena_t *a)
{
    g_configarena = a;
    memset(hashtab, 0, sizeof(hashtab));
}

static token_t I_NextToken(char *buf)
{
    int len;

    len = 0;
    while (*cursor && isspace((unsigned char) *cursor))
        cursor++;

    if (*cursor == '\0' || *cursor == '\n' || *cursor == ';')
        return TOKEN_EOF;
    
    if (*cursor == '=') {
        cursor++;
        return TOKEN_EQ;
    }
    
    if (*cursor == '"') {
        cursor++;
        while (*cursor && *cursor != '"') {
            if (len < MAXLINE - 1)
                buf[len++] = *cursor;
            cursor++;
        }
        if (*cursor == '"')
            cursor++;
        buf[len] = '\0';
        return TOKEN_ID;
    }

    while (*cursor && !isspace((unsigned char)*cursor)
           && *cursor != '=' && *cursor != ';') {
        if (len < MAXLINE - 1)
            buf[len++] = *cursor++;
    }
    buf[len] = '\0';

    return (len > 0) ? TOKEN_ID : TOKEN_EOF;
}

static struct nlist *I_ConfigLookup(const char *s)
{
    struct nlist *np;
    unsigned int h;

    h = U_Hash(s, strlen(s)) % HASHSIZE;
    for (np = hashtab[h]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

static struct nlist *I_ConfigInstall(const char *name, const char *defn)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = I_ConfigLookup(name)) == NULL) { /* not found */
        np = (struct nlist *) M_Alloc(g_configarena, sizeof(*np));
        if (np == NULL || (np->name = M_StrDup(g_configarena, name)) == NULL)
            return NULL;
        hashval = U_Hash(name, strlen(name)) % HASHSIZE;
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    if ((np->defn = M_StrDup(g_configarena, defn)) == NULL)
        return NULL;
    return np;
}

void I_ConfigLoad(const char *filename)
{
    FILE *fp;
    char line[MAXLINE];
    char k[MAXLINE], v[MAXLINE], trash[MAXLINE];

    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "I_ConfigLoad: couldn't open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), fp)) {
        cursor = line;
        if (I_NextToken(k) == TOKEN_ID && I_NextToken(trash) == TOKEN_EQ
            && I_NextToken(v) == TOKEN_ID)
            I_ConfigInstall(k, v);
    }

    fclose(fp);
    printf("I_ConfigLoad: loaded %s\n", filename);
}

const char *I_ConfigGetStr(const char *key)
{
    struct nlist *np;

    np = I_ConfigLookup(key);
    return (np) ? np->defn : NULL;
}


int I_ConfigGetInt(const char *key)
{
    const char *v = I_ConfigGetStr(key);
    return (v) ? atoi(v) : 0;
}

float I_ConfigGetFloat(const char *key)
{
    const char *v = I_ConfigGetStr(key);
    return (v) ? (float)atof(v) : 0.0f; /* @todo use strtof */
}
