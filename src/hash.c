/**
 * \file hash.c
 * \brief Fichier contenant les fonctions utiles à un HashMap. Code source venant de
Section 6.6 of The C Programming Language.
 * \author lfreyss
 * \version 0.1
 * \date 20180308
 *
 * Fichier contenant les fonctionnalités HASH .
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../header/typedef.h"

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0)
            return np; /* found */
    }
    return NULL; /* not found */
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}