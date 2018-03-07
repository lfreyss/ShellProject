/**
 * \file helper.h
 * \brief helper header.
 * \author vlambs
 * \version 0.1
 * \date 20180207
 *
 * Header principal.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef _LOG_H_
#define _LOG_H_

void resetLogFile();
void logCmd(char* cmdLine, FILE *f);

#endif
