/**
 * \file helper.h
 * \brief helper header.
 * \author lfreyss
 * \version 0.1
 * \date 20180207
 *
 * Header principal.
 *
 */


#ifndef _HELPER_H_
#define _HELPER_H_

#include "typedef.h"


char *readline(void);
int parseSpace(char* str, char* parsed[]);
void ltrim(char* str);
void rtrim(char* str);
void trim(char str[]);
int parseControlOperator(char* str, char** parsed);
int parseRedirectionFlux(char* str, char** parsed);
void addChar(char c, char* stringToAdd);
char** createMallocTab(int x, int y);
void copyContentFile(char* writefilename, char* readfilename);
bool fileIsEmpty();
void displayOutput(char* filename);

#endif
