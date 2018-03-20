/**
 * \file main.c
 * \brief Fichier de lancement.
 * \author vlambs
 * \version 0.1
 * \date 24 janvier 2018
 *
 * Fichier contenant les fonctionnalité .
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../header/tree.h"


bool isOperator(char* c)
{
    if ((strcmp ("||", c) == 0) || (strcmp ("&&", c) == 0) || (strcmp ("|", c) == 0) || (strcmp (">", c) == 0) || (strcmp ("<", c) == 0) || (strcmp (">>", c) == 0) || (strcmp ("<<", c) == 0))
        return true;
    return false;
}

node* newNode()
{
    node* temp = malloc(sizeof(node));
    temp->left = temp->right = NULL;
    temp->value = NULL;
    return temp;
};

node* constructTree(char **input, int sizeInput)
{ 
    node* rightLeaf = newNode();
    node* root = newNode();
    int i;
    if(sizeInput == -1)
        return NULL;

    if(!isOperator(input[sizeInput])) {
        if(sizeInput != -1) {
            char** parsedRedirectionInput = createCallocTab(strlen(input[sizeInput]),40);
            int size = parseRedirectionFlux(input[sizeInput],parsedRedirectionInput); // vérifie si l'input contient des opérateurs de redirection de flux
            if( size == 0){ // si non on est arrivé à une feuille
                rightLeaf->value = input[sizeInput];
            } else { // si oui, continuer la construction de l'arbre
                rightLeaf = constructTree(parsedRedirectionInput, size);
            }
        } else { // on est arrivé à la dernière commande
            rightLeaf->value = input[sizeInput];
        }
        sizeInput--;
    } 
    if(sizeInput == -1)
        return rightLeaf;

    if(isOperator(input[sizeInput])) {
        root->value = input[sizeInput];
        root->right = rightLeaf;
        root->left = constructTree(input, --sizeInput);
    }

    return root;
}


char* displayTree( node* noeud ){
    if ( noeud != NULL ){
        printf("\t\tNoeud..................... [%s]\n", noeud->value);
        printf("\t\t\tFils gauche du noeud [%s].. [%s]\n", noeud->value, displayTree(noeud->left));
        printf("\t\t\tFils droit  du noeud [%s].. [%s]\n", noeud->value, displayTree(noeud->right));
        return noeud->value;
    }
    return "nobody";
}
