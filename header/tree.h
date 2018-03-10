/**
 * \file tree.h
 * \brief librairie permettant l'utilisation d'un tree
 * \author lfreyss
 * \version 0.1
 * \date 25 janvier 2018
 *
 * Définition des variables, enum, struct.
 *
 */


#ifndef _SHELL_H_
#define _SHELL_H_

#include "typedef.h"


/**
 * \fn bool isOperator(char* c);
 * \brief Fonction permettant de déterminer si l'élément est un opérateur ou une commande
 * \author lfreyss
 * \param c -> élément à examiner
 * \return est un opérateur ou non
 */
bool isOperator(char* c);


/**
 * \fn node* newNode();
 * \brief Fonction permettant la création d'un noeud vide
 * \author lfreyss
 * \param 
 * \return
 */
node* newNode();

/**
 * \fn node* constructTree(char **input, int sizeInput);
 * \brief Fonction permettant de construire récursivement un arbre de commande
 * \author lfreyss
 * \param input -> le tableau de string qu'il faut transformer en arbre, sizeInput -> le nombre d'élément dans le tableau
 * \return Le noeud construit lors de l'itération de récursivité
 */
node* constructTree(char **input, int sizeInput);

/** 
 * \fn char* displayTree( node* noeud );
 * \brief Fonction peremttant de visualiser dans la sortie standard un arbre à partir d'un noeud spécifique
 * \author lfreyss
 * \param Noeud spécifique à partir du quel on affiche l'arbre
 * \return valeur du noeud
 */
char* displayTree( node* noeud );
#endif
