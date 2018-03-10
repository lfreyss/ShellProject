/**
 * \file typedef.h
 * \brief Définition des variables, enum, struct.
 * \author vlambs
 * \version 0.1
 * \date 24 janvier 2018
 *
 * Définition des variables, enum, struct.
 *
 */

#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

/**
 * \fn typedef struct _node
 * \brief Structure permettant à un noeud d'avoir une valeur,un fils droit et gauche
 * \author lfreyss
 */
typedef struct _node {
    char* value;
    struct _node *left;
    struct _node *right;
} node;

/**
 * \fn typedef int bool;
 * \brief Structure permettant l'utilisation de boolean
 * \author lfreyss
 */
typedef int bool;
#define true 1
#define false 0


/**
 * \fn struct nlist
 * \brief Structure permettant la création d'un dictionnaire au format [key][name]
 * \author lfreyss
 */
struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};


#endif
