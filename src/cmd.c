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
#include "../header/typedef.h"


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

bool runCommand(char **args){

  pid_t forkPid;
  pid_t waitPid;
  int status;

  forkPid = fork();
  if (forkPid == 0) {
    // On est dans le fils
    status = execvp(args[0], args);
    if (status == -1) {
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
  if(status != 0) 
    return false;
  else {
    return true;
  }
}

bool execute(char **args){
  bool status = false;
  if(args == NULL){
    return status;
  }
  else if(strcmp ("help", args[0]) == 0){
    runHelp();
  }
  else if (strcmp ("cd", args[0]) == 0){
    if (runCd(args) == 1){
      status = runCommand(args);
    }
  }
  else {
    status = runCommand(args);
  }
  return status;
}

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void runPipe(char **command1, char **command2)
{
    int fd[2];
    pid_t childPid;
    if (pipe(fd) != 0)
        error("failed to create pipe");

    if ((childPid = fork()) == -1)
        error("failed to fork");

    if (childPid == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        runCommand(command1);
    }
    else
    {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        runCommand(command2);
    }
}