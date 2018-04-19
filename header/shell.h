/**
 * \file shell.h
 * \brief Header principal.
 * \author lfreyss
 * \version 0.1
 * \date 24 janvier 2018
 *
 * Header principal.
 *
 */


#ifndef _SHELL_H_
#define _SHELL_H_

#include "typedef.h"

/**
 * \fn void addAlias(char* input);
 * \brief Fonction permettant l'ajout d'un alias dans une HashMap
 * \author lfreyss
 * \param input -> String entré par l'utilisateur commencant par la commande alias
 * \return
 */
void addAlias(char* input);

/**
 * \fn char* readTree(node* root);
 * \brief Fonction permettant de lire l'arbre de commande et de lancer le process des commandes
 * \author lfreyss
 * \param root -> noeud principale de l'arbre
 * \return
 */
char* readTree(node* root);

/**
 * \fn int runInBackground(char* completeInput, int index);
 * \brief Fonction permettant de lancer en arrière plan les commandes saisies
 * \author lfreyss
 * \param String contenant la saisie de l'entrée standard, numéro d'index du char & à retirer
 * \return
 */
int runInBackground(char* completeInput, int index);

/**
 * \fn void launchProcess(char* completeInput);
 * \brief Fonction permettant lancer la série de commande en avant plan
 * \author lfreyss
 * \param String contenant la saisie de l'entrée standard
 * \return Statut du shell (doit quitter : 0; continuer la boucle: 1)
 */
int launchProcess(char* completeInput);

/**
 * \fn void checkBatchMode(char* option, char* cmd);
 * \brief Fonction permettant de vérifier que les arguments pour le batch mode soient correctes et exécuter la commande si tout est ok
 * \author vlambs
 * \param String contenant l'option ("-b")
 * \param String contenant la commande à exécuter 
 * \return
 */
void checkBatchMode(char* option, char* cmd)

/**
 * \fn void launch(char* input)
 * \brief Fonction permettant fait les appels pour executer la commande (parsing, arbres, etc)
 * \author vlambs
 * \param String contenant la commande à exécuter 
 * \return 
 */
void launch(char* input)

/**
 * \fn void bash_loop(FILE *f);
 * \brief Fonction permettant de boucler notre programme tant que la commande exit n'est pas entré par l'utilisateur
 * \author lfreyss
 * \param fichier de log
 * \return
 */
void bash_loop(FILE *f);
#endif
