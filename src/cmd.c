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

  int saved_stdout = dup(1);
  int out; 
  int in;
  out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  in = open("in", O_RDONLY);
  dup2(out, 1);
  
  if(fileIsEmpty() == false){
    dup2(in,0);
  }
  
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
    close(out);
    close(in);
    dup2(saved_stdout, 1);
    close(saved_stdout);
  }

  if(status != 0) 
    return false;
  else {
    return true;
  }
}

bool runEcho(char* str) {
  int saved_stdout = dup(1);
  int out; 
  out = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  dup2(out, 1);
  printf("%s\n",str);
  close(out);    
  dup2(saved_stdout, 1);
  close(saved_stdout);
  return true;
}

bool execute(char **args){
  bool isSuccessfull = false;
  if(args == NULL){
    return isSuccessfull;
  }
  else if(strcmp ("help", args[0]) == 0){
    runHelp();
  }
  else if(strcmp ("echo", args[0]) == 0){
    runEcho(args[1]);
  }
  else if (strcmp ("cd", args[0]) == 0){
    if (runCd(args) == 1){
      isSuccessfull = runCommand(args);
    }
  }
  else {
    isSuccessfull = runCommand(args);
  }
  return isSuccessfull;
}

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void runPipe(char **cmd1, char **cmd2)
{
    int fd[2];
    pid_t childPid;
    pid_t waitPid;
    int status;
    if (pipe(fd) != 0)
        error("failed to create pipe");

    if ((childPid = fork()) == -1)
        error("failed to fork");

    if (childPid == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        //status = execvp(cmd1[0], cmd1);
        runCommand(cmd1);
        //error("close1");
        
    }
    else
    {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        //status = execvp(cmd2[0], cmd2);
        runCommand(cmd2);
        //error("close2");
    }
}

void runRedirection(char** cmd, char* outputFileName ) {
   int out;
  //char *grep_args[] = {"grep", "Villanova", NULL};

  // open input and output files

  //in = open("scores", O_RDONLY);
  out = open(outputFileName, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

  // replace standard input with input file

  //dup2(in, 0);

  // replace standard output with output file

  dup2(out, 1);

  // close unused file descriptors

  //close(in);
  close(out);

  // execute grep

  execvp(cmd[0],cmd);
}