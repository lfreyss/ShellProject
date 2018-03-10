/**
 * \file helper.c
 * \brief Fichier contenant les fonctions d'helper.
 * \author lfreyss
 * \version 0.1
 * \date 20180207
 *
 * Fichier contenant les fonctionnalité .
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../header/typedef.h"

char *readline(void)
{
  char *line = NULL;
  ssize_t bufsize = 0;
  getline(&line, &bufsize, stdin); // recupère la valeur de l'entrée standard
  return line;
}

int parseSpace(char* str, char* parsed[])
{
    int i;
    int  len_result;

    for (i = 0; i < 100; i++) {
        parsed[i] = strsep(&str, " ");
        if(parsed[i] != NULL) {
            len_result = strlen(parsed[i]);
            char* result = parsed[i];
            if(result[(len_result - 1)] == '\n'){
                result[(len_result - 1)] = '\0';
                parsed[i] = result;
            }
        }
     
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
    int j = 0;
    for(j = 0; j < i; j++) { //trim toutes les string obtenues
        trim(parsed[j]);
    }
    return i;
}

int parseString(char* str, char* parsed[], char* sep)
{
    int i;
    int  len_result;

    for (i = 0; i < 100; i++) {
        parsed[i] = strsep(&str, sep);
        if(parsed[i] != NULL) {
            len_result = strlen(parsed[i]);
            char* result = parsed[i];
            if(result[(len_result - 1)] == '\n'){
                result[(len_result - 1)] = '\0';
                parsed[i] = result;
            }
        }
     
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
    int j = 0;
    for(j = 0; j < i; j++) { //trim toutes les string obtenues
        trim(parsed[j]);
    }
    return i;
}

void ltrim(char * str)
{
    int strIndex = 0;
    int i;
    while(str[strIndex] == ' ' || str[strIndex] == '\t' || str[strIndex] == '\n')
        strIndex++;
    if(strIndex != 0)
    {
        i = 0;
        while(str[i + strIndex] != '\0')
        {
            str[i] = str[i + strIndex];
            i++;
        }
        str[i] = '\0'; //clos la string
    }
}

void rtrim(char * str)
{
    int strIndex;
    int lastIndex;
    lastIndex = strlen(str);
    strIndex = lastIndex;
    while(str[strIndex-1] == ' ' || str[strIndex-1] == '\t' || str[strIndex-1] == '\n')
        strIndex = strIndex-1;
    if(strIndex != lastIndex )
        str[strIndex] = '\0'; //clos la string
}

void trim(char str[]) {
    ltrim(str);
    rtrim(str);
}

void addChar(char c, char* stringToAdd) {
    if(c != '\n') {
        size_t len = strlen(stringToAdd);
        char* test = malloc(sizeof(len) +2);// longueur de la string + nouveau caractère + /0
        strcpy(test, stringToAdd);
        test[len] = c; // remplace le vieux /0 par le caractère
        test[len + 1] = '\0'; // clos la string
        strcpy(stringToAdd,test);
        free(test);
    }        
}

int parseControlOperator(char* str, char** parsed) {
    int i, k;
    int j = 0;
    for (i = 0; i < strlen(str); i++) { // parcours chaque caractère
        if(str[i] == '|' || str[i] == '&'){ 
            i++;
            if(str[i] == '|' || str[i] == '&') { // si on tombe sur && ou || alors nouveau string
                j++;
                addChar(str[i-1], parsed[j]);             
                addChar(str[i], parsed[j]);             
                j++;
            } else {
                i--;
                addChar(str[i], parsed[j]);  
            }
        } else 
            addChar(str[i], parsed[j]);                 
    }
    for(k = 0; k < j; k++) {
        trim(parsed[k]);
    }
    return j;
}

int parseRedirectionFlux(char* str, char** parsed) {
    int i, k;
    int j = 0;
    for (i = 0; i < strlen(str); i++) {
        if(str[i] == '|' || str[i] == '>' || str[i] == '<'){
            i++;
            j++;
            if(str[i] == '>' || str[i] == '<') { // si on tombe sur << ou >>
                addChar(str[i-1], parsed[j]);             
                addChar(str[i], parsed[j]);             
                j++;
            } else {
                i--;
                addChar(str[i], parsed[j]);  
                j++;
            }
        } else {
            addChar(str[i], parsed[j]);          
        }
        
    }
    for(k = 0;k < j; k++) {
        trim(parsed[k]);
    }
    return j;
}

char** createCallocTab(int x, int y) {
     char **a = calloc(x, sizeof(char *)); //calloc à la place de malloc pour être sur que le tableau de string est vivde
    for(int i = 0; i != x; i++) {
        a[i] = calloc(y, sizeof(char));
    }
    return a;
}

void copyContentFile(char* writefilename,char* readfilename, bool overide) {
    FILE *fp1, *fp2;
    int a;

    fp1 = fopen(readfilename, "r");
    if (fp1 == NULL) {
      puts("cannot open out file");
      exit(0);
    }
    if(overide == true) 
        fp2 = fopen(writefilename, "a"); //ajoute au contenu
    else
        fp2 = fopen(writefilename, "w"); // remplace le contenu
    if (fp2 == NULL) {
      puts("cannot open in file");
      fclose(fp1);
      exit(0);
    }
    while( (a = fgetc(fp1)) != EOF )
    {
      fputc(a, fp2);
    }

    fclose(fp1);
    fclose(fp2);
}

bool fileIsEmpty() {
    FILE *fp;
    fp = fopen("in", "r");
    int size;
    if (fp != NULL) {
        fseek (fp, 0, SEEK_END);
        size = ftell(fp);

        if (size == 0) {
            return true;
        }
    }
    return false;
}

void displayOutput(char* filename) {
    int c;
    FILE *file;
    file = fopen(filename, "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }
}

void addContentToFile(char* str) {
    FILE *file;
    file = fopen("in", "a");

    if (file == NULL){
        perror("Error has occured, can't open the file");
    }
    fprintf(file, "%s%s", str, "\n");  
    fclose(file);  
}
