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

  bool isOperator(char* c);

  // Utility function to do inorder traversal
  void inorder(node *t);

  // A utility function to create a new node
  node* newNode(char* v);

  node* constructTree(char* postfix);

#endif
