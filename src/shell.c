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


/**
 * \fn int main (void)
 * \brief Fonction de destruction de l'objet Str_t.
 * \author vlambs
 * \param argc(int) et argv (char*)
 * \return EXIT_SUCCESS
 */
int main(int argc, char* argv)
{
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

  do {
    char *line;
    printf("PROMPT>>> ");
    scanf(" %s", &line);
    //args = lsh_split_line(line);
    status = execute(&line);

  } while (status);
}
