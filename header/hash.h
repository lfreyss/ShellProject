
/**
 * \file hash.h
 * \brief Fichier contenant les fonctions utiles à un HashMap. Code source venant de
Section 6.6 of The C Programming Language.
 * \author lfreyss
 * \version 0.1
 * \date 20180308
 *
 * Fichier contenant les fonctionnalités HASH .
 *
 */

#ifndef _HASH_H_
#define _HASH_H_

#include "typedef.h"

unsigned hash(char *s);

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s);
/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn);

#endif
