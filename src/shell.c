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
#include <../header/main.h>


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

/**
 * \fn void bash_loop (void)
 * \brief Fonction de test.
 * \author vlambs
 * \param void
 * \return void
 */
void bash_loop()
{
  printf("Hello world");
}
