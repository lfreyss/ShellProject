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

void addAlias(char* input);
char* readTree(node* root);
void bash_loop(FILE *f);
#endif
