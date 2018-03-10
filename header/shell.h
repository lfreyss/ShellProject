/**
 * \file main.h
 * \brief Header principal.
 * \author vlambs
 * \version 0.1
 * \date 24 janvier 2018
 *
 * Header principal.
 *
 */


#ifndef _SHELL_H_
#define _SHELL_H_

#include "typedef.h"

/**
 * \fn void addAlias(char* input);
 * \brief Fonction permettant l'ajout d'un alias dans une HashMap
 * \author lfreyss
 * \param input -> String entré par l'utilisateur commencant par la commande alias
 * \return
 */
void addAlias(char* input);

/**
 * \fn char* readTree(node* root);
 * \brief Fonction permettant de lire l'arbre de commande et de lancer le process des commandes
 * \author lfreyss
 * \param root -> noeud principale de l'arbre
 * \return
 */
char* readTree(node* root);

/**
 * \fn void bash_loop(FILE *f);
 * \brief Fonction permettant de boucler notre programme tant que la commande exit n'est pas entré par l'utilisateur
 * \author lfreyss
 * \param fichier de log
 * \return
 */
void bash_loop(FILE *f);
#endif
