
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


#ifndef _CMD_H_
#define _CMD_H_

#include "typedef.h"
#include "helper.h"


void runHelp();
int execute(char **args);
void printDir();
int runCommand(char **args);
int runCd(char **args);
void error(const char *msg);
void runPipe(char **command1, char **command2);
void runRedirection(char** cmd, char* outputFileName );
#endif

