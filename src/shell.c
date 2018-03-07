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
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../header/shell.h"
#include "../header/tree.h"
#include "../header/stack.h"
#include "../header/cmd.h"
#include "../header/log.h"
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
  scanf(" %s", line);N
  node* t = newNode(line);
  printf("line %s", line);

  printf("peek>>>%s ", t->value);*/
  bash_loop();
  return EXIT_SUCCESS;
}


bool status = false;

char* readTree(node* root) {
    if(root != NULL) {
      
          readTree(root->left);
        
        printf("Commande : %s\n", root->value);
        if(isOperator(root->value)) {
            if(strcmp ("&&", root->value) == 0) {
              if(status == true) {
                readTree(root->right);
              }
            } else if(strcmp ("||", root->value) == 0) {
              if(status == false) {
                readTree(root->right);
              }
            } else if(strcmp (">", root->value) == 0) {
              //readTree(root->right);
              copyContentFile(root->right->value);

            }  else if(strcmp ("|", root->value) == 0) {
              // char** arg1 = createMallocTab(5);// root->value, NULL };
              // parseSpace(root->left->value, arg1);
              // char** arg2 = createMallocTab(5);// root->value, NULL };
              // parseSpace(root->right->value, arg2);
              // runPipe(arg1,arg2);
              int saved_stin = dup(0);

              copyContentFile("in");
              readTree(root->right);
              fclose(fopen("in", "w"));
              dup2(saved_stin, 0);
              close(saved_stin);
            }
        } else {
          char** arguments = createMallocTab(5);// root->value, NULL };
          parseSpace(root->value, arguments);
          status = execute(arguments);
        }
        return root->value;
    }

    return "end";   
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

  int loopAlive = 1;
  char* line;
  do {
    printDir();
    char* input = readline();
    char** parsedInput = createMallocTab(10);
    

    int sizeInput = parseControlOperator(input, parsedInput);
    
    // printf("1 - %s\n", parsedInput[0]);
    // printf("2 - %s\n", parsedInput[1]);
    // printf("3 - %s\n", parsedInput[2]);
    // printf("4 - %s\n", parsedInput[3]);
    // printf("5 - %s\n", parsedInput[4]);
    if(strcmp ("exit", parsedInput[0]) == 0) {
      loopAlive = 0 ;
    } else {
      node* root = constructTree(parsedInput, sizeInput);
      displayTree( root);
      readTree(root);
      free(parsedInput);
    }

  } while (loopAlive);

}
