/**
 * \file main.c
 * \brief Fichier de lancement.
 * \author vlambs
 * \version 0.1
 * \date 24 janvier 2018
 *
 * Fichier contenant les fonctionnalité .
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../header/tree.h"
#include "../header/stack.h"
// A utility function to check if 'c'
// is an operator
bool isOperator(char* c)
{
    if ((strcmp ("||", c) == 0) || (strcmp ("&&", c) == 0))
        return true;
    return false;
}

// Utility function to do inorder traversal
void inorder(node *t)
{
    if(t)
    {
        inorder(t->left);
        printf("%s ", t->value);
        inorder(t->right);
    }
}

// A utility function to create a new node
node* newNode(char* v)
{
    node* temp = malloc(sizeof(node));
    temp->left = temp->right = NULL;
    temp->value = v;
    return temp;
};

node* constructTree(char* postfix)
{
    Stack* stack = createStack(20);
    node *t, *t1, *t2;
    printf("const tree %s", postfix);
    // Traverse through every character of
    // input expression
    for (int i=0; postfix[i]!='\0'; i++)
    {
      printf("%s\n", postfix[i]);
        // If operand, simply push into stack
        if (!isOperator(postfix[i]))
        {
            t = newNode(postfix[i]);
            push(stack, t);
        }
        else // operator
        {
            t = newNode(postfix[i]);

            // Pop two top nodes
            t1 = peek(stack); // Store top
            pop(stack);      // Remove top
            t2 = peek(stack);
            pop(stack);

            //  make them children
            t->right = t1;
            t->left = t2;

            // Add this subexpression to stack
            push(stack, t);
        }
    }

    //  only element will be root of expression
    // tree
    t = peek(stack);
    pop(stack);

    return t;
}
