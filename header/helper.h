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

/**
 * \fn char *readline(void);
 * \brief Fonction permettant de lire la saisie de l'entrée standard
 * \author lfreyss
 * \param 
 * \return Saisie de l'entrée standard
 */
char *readline(void);

/**
 * \fn int parseSpace(char* str, char* parsed[]);
 * \brief Fonction permettant de séparer une chaine de caractère par des espaces
 * \author lfreyss
 * \param str -> chaine de caractère à séparer; parsed[] -> tab de string contenant les string séprarés
 * \return
 */
int parseSpace(char* str, char* parsed[]);
int parseString(char* str, char* parsed[], char* sep);

/**
 * \fn void ltrim(char* str);
 * \brief Fonction permettant de supprimer les espaces, les tabulations et sauts de ligne en début de string
 * \author lfreyss
 * \param String à examiner
 * \return
 */
void ltrim(char* str);

/**
 * \fn void rtrim(char* str);
 * \brief Fonction permettant de supprimer les espaces, les tabulations et sauts de ligne en fin de string
 * \author lfreyss
 * \param String à examiner
 * \return
 */
void rtrim(char* str);

/**
 * \fn void trim(char str[]);
 * \brief Fonction permettant d'appeler le rtrim et ltrim en un seul appel
 * \author lfreyss
 * \param String à examiner
 * \return
 */
void trim(char str[]);

/**
 * \fn void addChar(char c, char* stringToAdd);
 * \brief Concatène un caractère à une chaine de caractère
 * \author lfreyss
 * \param Caractère à concatèner, chaine de caractère à concatèner
 * \return
 */
void addChar(char c, char* stringToAdd);

/**
 * \fn int parseControlOperator(char* str, char** parsed);
 * \brief Fonction permettant de découper une string par les opérateurs de control, à savoir && et ||
 * \author lfreyss
 * \param String a découper, tab de string contenant la chaine de caractère découpé
 * \return nombre de string dans le tableau
 */
int parseControlOperator(char* str, char** parsed);

/**
 * \fn int parseRedirectionFlux(char* str, char** parsed);
 * \brief Fonction permettant de découper une string par les opérateurs de redirection de flux, à savoir |,&,<,>,<<,>>
 * \author lfreyss
 * \param String a découper, tab de string contenant la chaine de caractère découpé
 * \return nombre de string dans le tableau
 */
int parseRedirectionFlux(char* str, char** parsed);

/**
 * \fn char** createCallocTab(int x, int y);
 * \brief Fonction permettant de créer un tableau de chaine de caractère
 * \author lfreyss
 * \param x -> nombre de chaine de caractère, y -> nombre de caractère dans une chaine de caractère
 * \return Le tableau de chaine de caractère
 */
char** createCallocTab(int x, int y);

/**
 * \fn void copyContentFile(char* writefilename, char* readfilename, bool overide);
 * \brief Fonction permettant la copie du contenu d'un fichier vers un autre
 * \author lfreyss
 * \param writefilename -> fichier de destination, readfilename -> fichier source, overide -> ajouter au contenu ou le remplacer
 * \return 
 */
void copyContentFile(char* writefilename, char* readfilename, bool overide);

/**
 * \fn bool fileIsEmpty();
 * \brief Fonction permettant de check si un fichier est vide ou non
 * \author lfreyss
 * \param 
 * \return
 */
bool fileIsEmpty();

/**
 * \fn void displayOutput(char* filename);
 * \brief Fonction permettant de afficher le contenu d'un fichier sur la sortie standard
 * \author lfreyss
 * \param  Nom du fichier
 * \return
 */
void displayOutput(char* filename);

/**
 * \fn void addContentToFile(char* str);
 * \brief Fonction permettant de rajouter du contenu à un fichier
 * \author lfreyss
 * \param String à ajouter au contenu du fichier
 * \return
 */
void addContentToFile(char* str);

#endif
