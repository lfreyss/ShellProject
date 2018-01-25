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

typedef struct _node {
    char* value;
    struct _node *left, *right;
} node;



// A structure to represent a stack
typedef struct _stack
{
   int top;
   unsigned capacity;
   node* array;
} Stack;

typedef int bool;
#define true 1
#define false 0


#endif
