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


// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\n%s >>>", cwd);
}


void runHelp(){
  printf("-------------AIDE-------------\n");
  printf("Voici la liste des built-in commandes:\n");
  printf("  - exit\n");
  printf("  - help\n");
  printf("  - cd [args]\n");
  printf("  - ls [args]\n");
  printf("Plus d'information sur les commandes en accédant à leur manuel.\n");
}

int runCd(char **args){
  int error;
  error = 1;
   if (args[1] == NULL) {
    printf("Utilisation incorrecte de la commande CD\n");
    error = 0;
  } else {
    if (chdir(args[1]) != 0) {
      printf("Le dossier n'existe pas.\n");
      error = 0;
    }
  }
  return error;
}

int runCommand(char **args){

  pid_t forkPid;
  pid_t waitPid;
  int status;

  forkPid = fork();
  if (forkPid == 0) {
    // On est dans le fils
    if (execvp(args[0], args) == -1) {
      printf("Une erreur est survenue lors de l'execution de la commande.\n");
    }
    exit(EXIT_FAILURE);
  } else if (forkPid < 0) {
    printf("Une erreur est survenue lors de la création du processus fils.\n");
  } else {
    // On est dans le père
    do {
      waitPid = waitpid(forkPid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int execute(char **args){
  int status = 1;
  if(args == NULL){
    return 1;
  }
  
  else if(strcmp ("help", args[0]) == 0){
    runHelp();
  }
  else if (strcmp ("cd", args[0]) == 0){
    if (runCd(args) == 1){
      runCommand(args);
    }
  }
  else {
    status = runCommand(args);
  }
  return 1;
}

bool status = false;

char* readTree(node* root) {
    if(root != NULL) {
        readTree(root->left);
        
        printf("Commande : %s\n", root->value);
        if(isOperator(root->value)) {
            if(strcmp ("&&", root->value) == 0) {
                status = execute(root->left->value);
                if(status == true) {
                    readTree(root->right);
                }
            } else if(strcmp ("||", root->value) == 0) {
                 if(status == false) {
                    readTree(root->right);
                }
            } else if(strcmp ("|", root->value) == 0) {
                readTree(root->right);
            } else if(strcmp (">", root->value) == 0) {
                readTree(root->right);
            }
        } else {
          char *arguments[] = { root->value, NULL };
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

    char** parsedInput = malloc(sizeof(char*) * 10);
    for(int i = 0; i < 10; i++) {
      parsedInput[i] = malloc(sizeof(char)*40);
    }

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
