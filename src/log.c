/**
 * \file log.c
 * \brief Interaction fichier log
 * \author vlambs
 * \version 0.1
 * \date 07 mars 2018
 *
 * Classe d'interaction avec fichier de log.
 *
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * \fn void logCmd (void)
 * \brief Insérer une ligne saisien dans le fichier de log
 * \author vlambs
 * \param char*, FILE
 * \return void
 */
void logCmd(char* cmdLine, FILE *f) {
    if(f == NULL){
        printf("An error happened while logging the command line.");
        exit(1);
    }
    fprintf(f, "%s\n", cmdLine);
}
/**
 * \fn void resetLogFile (void)
 * \brief Vider le fichier de log des commandes
 * \author vlambs
 * \param void
 * \return void
 */
void resetLogFile(){
    FILE *f = fopen("logCmd.txt", "wb");
    if(!f){
        printf("An error happened while resetting the log file.");
        exit(1);
    }
    fclose(f);
}