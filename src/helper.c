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
    return i;
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

