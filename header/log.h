/**
 * \file log.h
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

/**
 * \fn char resetLogFile();
 * \brief Méthode permettant de vider le fichier de log
 * \author vlambs
 * \param 
 * \return nothing
 */
void resetLogFile();

/**
 * \fn char logCmd(char*);
 * \brief Méthode permettant d'insérer une ligne dans le fichier de log
 * \author vlambs
 * \param 
 * \return nothing
 */
void logCmd(char* cmdLine);

#endif
