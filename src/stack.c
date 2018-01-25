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
    printf("node value avant ++ %s\n", stack->array[stack->top].value);

    if (isFull(stack))
        return;
    //stack->top = stack->top+1;
    stack->array[++stack->top] = *item;
    printf("node value après ++ %s\n", stack->array[stack->top].value);

    //printf("%s pushed to stack\n", item->value);
}

// Function to remove an item from stack.  It decreases top by 1
node* pop(Stack* stack)
{
    node* n = &stack->array[stack->top];
    printf("node value avant -- %s\n", stack->array[stack->top].value);
    stack->top = stack->top-1;
    printf("node value après -- %s\n", stack->array[stack->top].value);
    printf("node value après -- %s\n", stack->array[stack->top-1].value);
    printf("node value après -- %s\n", stack->array[stack->top-2].value);


    printf("%d\n", stack->top);
    return n;
}

node* peek(Stack* stack)
{
  printf("peek %d\n", stack->top);
    return &stack->array[stack->top];
}
