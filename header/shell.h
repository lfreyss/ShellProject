/**
 * \file main.h
 * \brief Header principal.
 * \author vlambs
 * \version 0.1
 * \date 24 janvier 2018
 *
 * Header principal.
 *
 */


#ifndef _SHELL_H_
#define _SHELL_H_

#include "typedef.h"
#include "helper.h"

int execute(char **args);
void printDir();
int runCommand(char **args);
int runCd(char **args);
char* readTree(node* root);
void runHelp();
void bash_loop();
#endif
