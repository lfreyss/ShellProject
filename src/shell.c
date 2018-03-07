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
        if(strcmp ("<", root->value) == 0) {
            int saved_stin = dup(0);
            trim(root->right->value);
            copyContentFile("in",root->right->value);
            readTree(root->right);
            //fclose(fopen("in", "w"));
            dup2(saved_stin, 0);
            close(saved_stin);
        } else
          readTree(root->left);
        
        printf("Commande : %s\n", root->value);
        if(isOperator(root->value)) {
            if(strcmp ("&&", root->value) == 0) {
              if(status == 1) {
                displayOutput("out");
                readTree(root->right);
                status = 1;
              }
            } else if(strcmp ("||", root->value) == 0) {
              if(status == 0) {
                readTree(root->right);
              }
            } else if(strcmp (">", root->value) == 0) {
              //readTree(root->right);
              trim(root->right->value);
              copyContentFile(root->right->value, "out");
              fclose(fopen("out", "w"));

            } else if(strcmp ("|", root->value) == 0) {
              int saved_stin = dup(0);
              copyContentFile("in", "out");
              readTree(root->right);
              fclose(fopen("in", "w"));
              dup2(saved_stin, 0);
              close(saved_stin);
            }
        } else {
          char** arguments = createMallocTab(5,40);// root->value, NULL };
          parseSpace(root->value, arguments);
          status = execute(arguments);
          free(arguments);
    //freeMallocTab(arguments, 5);
          
        }
        return root->value;
    }

    return "end";   
}

void flush_stdin() {
    char c;
    ungetc('\n', stdin); // ensure that stdin is always dirty
    while(((c = getchar()) != '\n') && (c != EOF));
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
    //flush_stdin();
    char** parsedInput;
    char* input = readline();
    parsedInput = createMallocTab(10,40);
    //freeMallocTab(parsedInput,10);
    
    // printf("input: %s\n",input);

    int sizeInput = parseControlOperator(input, parsedInput);
    free(input);
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
      //displayTree( root);
      readTree(root);
      displayOutput("out");
    }

    
  } while (loopAlive);

}
