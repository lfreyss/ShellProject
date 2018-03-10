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

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../header/hash.h"
#include "../header/tree.h"
#include "../header/cmd.h"
#include "../header/log.h"
#include "../header/typedef.h"
#include "../header/shell.h"


bool status = false;

char* readTree(node* root) {
    if(root != NULL) {
        if(strcmp ("<", root->value) == 0) { // effectue la commande sur le contenu du fichier root->right
            int saved_stin = dup(0);
            trim(root->right->value);
            copyContentFile("in",root->right->value, false);
            readTree(root->left);
            fclose(fopen("in", "w"));
            dup2(saved_stin, 0);
            close(saved_stin);
        } else if(strcmp ("<<", root->value) == 0) { //effectue la commande sur un contenu multiple ligne de l'entrée standard
            int saved_stin = dup(0);
            trim(root->right->value);
            char* input = readline();
            trim(input);
            while(strcmp (input, root->right->value) != 0) {// ajoute chaque ligne saisie au fichier in
              addContentToFile(input);
              input = readline();
              trim(input); 
            } 
            
            readTree(root->left);
            fclose(fopen("in", "w"));
            dup2(saved_stin, 0);
            close(saved_stin);
        } else
          readTree(root->left);
        
        //printf("Commande : %s\n", root->value);
        if(isOperator(root->value)) {
            if(strcmp ("&&", root->value) == 0) { // s'effectue si la commande précédente a réussie
              if(status == 1) {
                displayOutput("out");
                readTree(root->right);
                status = 1;
              }
            } else if(strcmp ("||", root->value) == 0) {//s'effectue si la commande précédente n'a pas réussie
              if(status == 0) {
                readTree(root->right);
              }
            } else if(strcmp (">", root->value) == 0) { // écrit dans un fichier root->right->value le resultat de la commande
              //readTree(root->right);
              trim(root->right->value);
              copyContentFile(root->right->value, "out", false);
              fclose(fopen("out", "w"));

            } else if(strcmp (">>", root->value) == 0) { // ajoute au fichier root->right->value le resultat de la commande
              //readTree(root->right);
              trim(root->right->value);
              copyContentFile(root->right->value, "out", true);
              fclose(fopen("out", "w"));

            } else if(strcmp ("|", root->value) == 0) { // effectue la commande root->right->value sur le resutlat de la commande root->left->value contenu dans le fichier in
              int saved_stin = dup(0);
              copyContentFile("in", "out", false);
              readTree(root->right);
              fclose(fopen("in", "w"));
              dup2(saved_stin, 0);
              close(saved_stin);
            }
        } else { //execute la commande
          char** arguments = createCallocTab(5,40);
            //vérifie si la saisie est un alias
          struct nlist* alias = lookup(root->value);
          if(alias != NULL) {
            root->value = alias->defn;
          }
          
          parseSpace(root->value, arguments);

          status = execute(arguments);
          free(arguments);
        }
        return root->value;
    }

    return "end";   
}
void addAlias(char* input) {
  const char delimiters[] = "=";
  char *alias = strtok (input, " "); // supprime la commande alias
  char *name = strtok (NULL, delimiters);   // sépare le nom de la définition pour la HASHMAP
  char *def = strtok (NULL, delimiters);  
  struct nlist* hash = install(name,def);
}

void bash_loop(FILE *f)
{

  int loopAlive = 1;
  char* line;
  do {
    printDir();
    char** parsedInput;
    char* input = readline(); // attend une saisie
    if(input[0] == 'a' && input[1] == 'l' && input[2] == 'i' && input[3] == 'a' && input[4] == 's' ) { // si commande alias
      trim(input);
      addAlias(input);
    } else {
      trim(input);

    
      parsedInput = createCallocTab(10,40);
      
      //printf("input: %s\n",input);

      int sizeInput = parseControlOperator(input, parsedInput); // sépare la saisie par les opérateurs && et ||
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
        displayTree( root);
        readTree(root);
        displayOutput("out");
      }    
    }
    
  } while (loopAlive);

}


int main(int argc, char* argv)
{
  resetLogFile();
  FILE *f = fopen("logCmd.txt", "w");
  bash_loop(f);
  fclose(f);
  return EXIT_SUCCESS;
}