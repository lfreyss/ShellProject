/**
 * \file cmd.h
 * \brief Fichier contenant les fonctions utiles aux commandes shell
 * \author lfreyss
 * \version 0.1
 * \date 20180301
 *
 * Fichier contenant les fonctionnalités cmd .
 *
 */


#ifndef _CMD_H_
#define _CMD_H_

#include "typedef.h"
#include "helper.h"

/**
 * \fn void runHelp()
 * \brief Fonction permettant la lecture d'un help
 * \author vlambs
 * \param 
 * \return void
 */
void runHelp();

/**
 * \fn int execute(char **args)
 * \brief Fonction permettant de rediriger les commandes vers les fonctions d'executions corespondantes
 * \author vlambs
 * \param tableau de string contenant la commande a éxécuter et ses arguments/options
 * \return void
 */
int execute(char **args);

/**
 * \fn void printDir()
 * \brief Fonction permettant d'afficher le dossier courant lors de l'attente d'une saisie dans l'entrée standard
 * \author lfreyss
 * \param void
 * \return void
 */
void printDir();

/**
 * \fn int runCommand(char **args)
 * \brief  Fonction permettant l'execution via un fork et execvp des commandes simples du shell
 * \author vlambs/lfreyss
 * \param tableau de string contenant la commande a éxécuter et ses arguments/options
 * \return Succès de la commande ou non
 */
int runCommand(char **args);

/**
 * \fn int runCd(char **args)
 * \brief Fonction permettant l'execution de la fonction build in cd
 * \author vlambs
 * \param tableau de string contenant la commande a éxécuter et ses arguments/options
 * \return Succès de la commande ou non
 */
int runCd(char **args);

/**
 * \fn bool runEcho(char* str)
 * \brief Fonction permettant l'exectuion de la fonction build in echo
 * \author lfreyss
 * \param tableau de string contenant la commande a éxécuter et ses arguments/options
 * \return Succès de la commande ou non
 */
bool runEcho(char* str);
#endif

