/**
 * \file main.c
 * \brief Fichier de lancement.
 * \author vlambs
 * \version 0.1
 * \date 24 janvier 2018
 *
 * Fichier de lancement.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../header/shell.h"
#include "../header/tree.h"
#include "../header/stack.h"
/**
 * \fn int main (void)
 * \brief Fonction de destruction de l'objet Str_t.
 * \author vlambs
 * \param argc(int) et argv (char*)
 * \return EXIT_SUCCESS
 */
int main(int argc, char* argv)
{
  /*char *line;
  printf("PROMPT>>> ");
  scanf(" %s", line);
  node* t = newNode(line);
  printf("line %s", line);

  printf("peek>>>%s ", t->value);*/
  bash_loop();
  return EXIT_SUCCESS;
}


int execute(char* args) {
  int status = 1;
  if(strcmp ("exit", args) == 0) {
    status = 0;
  } else {
    printf("%s\n", args);
  }
  return status;
}

/**
 * \fn void bash_loop (void)
 * \brief Fonction de test.
 * \author vlambs
 * \param void
 * \return void
 */
void bash_loop()
{

  int status;
  Stack* stack = createStack(20);
  char line[20];
  do {

    printf("PROMPT>>> ");
    scanf(" %s", line);
    node* t = newNode(line);
    push(stack,t);
    //args = lsh_split_line(line);
    status = execute(&line);

  } while (status);
    printf("peek>>>%s\n ", peek(stack)->value);
    printf("pop>>>%s \n", pop(stack)->value);



    printf("peek>>>%s \n", peek(stack)->value);
    printf("pop>>>%s \n", pop(stack)->value);
}
