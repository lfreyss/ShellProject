/**
 * \file stack.h
 * \brief librairie permettant l'utilisation du file d'attente
 * \author lfreyss
 * \version 0.1
 * \date 25 janvier 2018
 *
 * Définition des variables, enum, struct.
 *
 */

 #ifndef _STACK_H_
 #define _STACK_H_
#include "typedef.h"

  // function to create a stack of given capacity. It initializes size of
  // stack as 0
  Stack* createStack(unsigned capacity);

  // Stack is full when top is equal to the last index
  int isFull(Stack* stack);
  // Stack is empty when top is equal to -1
  int isEmpty(Stack* stack);
  // Function to add an item to stack.  It increases top by 1
  void push(Stack* stack, node* item);
  // Function to remove an item from stack.  It decreases top by 1
  node* pop(Stack* stack);
  // FUnction to get the top node
  node* peek(Stack* stack);

void afficherPile( Stack *p );


#endif
