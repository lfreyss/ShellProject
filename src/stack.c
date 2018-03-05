// C program for array implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../header/stack.h"


// function to create a stack of given capacity. It initializes size of
// stack as 0
Stack* createStack(unsigned capacity)
{
    Stack* stack = malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = malloc(stack->capacity * sizeof(node));
    return stack;
}

// Stack is full when top is equal to the last index
int isFull(Stack* stack)
{   return stack->top == stack->capacity - 1; }

// Stack is empty when top is equal to -1
int isEmpty(Stack* stack)
{   return stack->top == -1;  }

// Function to add an item to stack.  It increases top by 1
void push(Stack* stack, node* item)
{
    if (isFull(stack))
        return;
    if(item->left != NULL) {
        printf("item left leaf %s\n", item->left->value);
    } 
    if(item->right != NULL) {
        printf("item right leaf %s\n", item->right->value);
    } 
    stack->array[++stack->top] = *item;
    printf("%s item to stack\n", item->value);
    printf("push top : %d \n", stack->top);   
    if(stack->top != -1) {
        if(peek(stack)->left != NULL) {
             printf("item left leaf after %s\n", item->left->value);
            peek(stack)->left = item->left;
            printf("pile left leaf %s\n", peek(stack)->left->value);
        } 
        if(peek(stack)->right != NULL) {
            printf("pile right leaf %s\n", peek(stack)->right->value);
        } 
    }
   
}

// Function to remove an item from stack.  It decreases top by 1
node* pop(Stack* stack)
{
    node* n = &stack->array[stack->top--];
    printf("pop n : %s \n", n->value);
    return n;
}

node* peek(Stack* stack)
{
    return &stack->array[stack->top];
}


/**
* \fn void afficherPile( PILE *p )
* \brief ProcÃ©dure affichant le contenu de la pile p
*/
void afficherPile( Stack *p ){

    if ( isEmpty(p) ){
        printf("La pile est vide\n");
        return;
    }

    printf("Pile.....................:\n");
    Stack *_m = p;
    int top = _m->top;
    while ( top != -1 ){
        node* noeud = &_m->array[top];
        printf("\t\t\t[%s]\n",noeud->value);
        top--;
    }

}