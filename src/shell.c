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
#include "../header/shell.h"
#include "../header/tree.h"
#include "../header/stack.h"
#include "../header/cmd.h"
#include "../header/log.h"
/**
 * \fn int main (void)
 * \brief Main
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
  resetLogFile();
  FILE *f = fopen("logCmd.txt", "w");
  bash_loop(f);
  fclose(f);
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
            } else if(strcmp ("|", root->value) == 0) {
              char** arg1 = createMallocTab(5);// root->value, NULL };
              parseSpace(root->left->value, arg1);
              char** arg2 = createMallocTab(5);// root->value, NULL };
              parseSpace(root->right->value, arg2);
              runPipe(arg1,arg2);

            } else if(strcmp (">", root->value) == 0) {
              readTree(root->right);
            }
        } else {
          
          char** arguments = createMallocTab(5);// root->value, NULL };
          parseSpace(root->value, arguments);
          //status = execute(arguments);
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
void bash_loop(FILE *f)
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
      logCmd(input, f);
      node* root = constructTree(parsedInput, sizeInput);
      displayTree( root);
      readTree(root);
      free(parsedInput);
    }

  } while (loopAlive);

}
