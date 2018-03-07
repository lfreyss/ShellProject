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
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line, &bufsize, stdin);
  return line;
}

// function for parsing command words
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
    for(j = 0; j < i; j++) {
        trim(parsed[j]);
        printf("whitout space:%s\n", parsed[j]);
    }
    return i;
}
/**
 * Enlève les espaces en début de chaine
 */
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
        str[i] = '\0'; // Make sure that string is NULL terminated
    }
}

/**
 * Enlève les espaces en fin de chaine
 * 
 *  
 */
void rtrim(char * str)
{
    int strIndex;
    int lastIndex;
    lastIndex = strlen(str);
    strIndex = lastIndex;
    while(str[strIndex] == ' ' || str[strIndex] == '\t' || str[strIndex] == '\n')
        strIndex--;
    if(strIndex != lastIndex )
        str[strIndex] = '\0'; // Make sure that string is NULL terminated
}

void trim(char str[]) {
    ltrim(str);
    rtrim(str);
}

void addChar(char c, char* stringToAdd) {
    if(c != '\n') {
        size_t len = strlen(stringToAdd);
        char* test = malloc(sizeof(len) +2);
        strcpy(test, stringToAdd);
        test[len] = c; /* we overwriting the null-character with another one */
        test[len + 1] = '\0';
        //test[len] = '\0'; /* to make the string null-terminated again */
        strcpy(stringToAdd,test);
        free(test);
    }        
}

int parseControlOperator(char* str, char** parsed) {
    int i;
    int j = 0;
    //char* testtest = malloc(sizeof(char)*15));
    for (i = 0; i < strlen(str); i++) {
        if(str[i] == '|' || str[i] == '&'){
            i++;
            if(str[i] == '|' || str[i] == '&') {
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
    return j;
}

int parseRedirectionFlux(char* str, char** parsed) {
    int i;
    int j = 0;
    //char* testtest = malloc(sizeof(char)*15));
    for (i = 0; i < strlen(str); i++) {
        if(str[i] == '|' || str[i] == '>'){
            j++;
            addChar(str[i], parsed[j]);             
            j++;

        } else {
            addChar(str[i], parsed[j]);          
        }
        
    }
    return j;
}

char** createMallocTab(int size) {
    char** tab = malloc(sizeof(char*) * size);
    for(int i = 0; i < size; i++) {
      tab[i] = malloc(sizeof(char)*40);
    }
    return tab;
}

void copyContentFile(char* filename) {
    FILE *fp1, *fp2;
    int a;

    fp1 = fopen("out", "r");
    if (fp1 == NULL) {
      puts("cannot open out file");
      exit(0);
    }

    fp2 = fopen(filename, "w");
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
