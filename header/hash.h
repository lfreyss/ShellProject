
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

/**
 * \fn struct nlist *lookup(char *s);
 * \brief Fonction permettant de parcourir la HashMap et de trouver l'élement voulu
 * \author lfreyss
 * \param chaine de caractère que l'on recherche
 * \return Struct nlist recherchée ou null si non trouvée
 */
struct nlist *lookup(char *s);

/**
 * \fn bool nlist *install(char *name, char *defn);
 * \brief Fonction permettant de rajouter un élément à la HashMap
 * \author lfreyss
 * \param name -> nom du hashmap; defn -> valeur du hashmap
 * \return nlist que l'on vient de rajouter
 */
struct nlist *install(char *name, char *defn);

#endif
