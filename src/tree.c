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
#include "../header/stack.h"
// A utility function to check if 'c'
// is an operator
bool isOperator(char* c)
{
    if ((strcmp ("||", c) == 0) || (strcmp ("&&", c) == 0) || (strcmp ("|", c) == 0) || (strcmp (">", c) == 0))
        return true;
    return false;
}

// Utility function to do inorder traversal
void inorder(node *t)
{
    if(t)
    {
        inorder(t->left);
        printf("%s ", t->value);
        inorder(t->right);
    }
}

// A utility function to create a new node
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
            
            char** parsedControlInput = malloc(strlen(input[sizeInput]) * sizeof(char*));
            for (int i = 0; i < strlen(input[sizeInput]); i++)
                parsedControlInput[i] = malloc((40) * sizeof(char)); 

            int size = parseRedirectionFlux(input[sizeInput],parsedControlInput);
            if( size == 0){
                rightLeaf->value = input[sizeInput];
            } else {
                rightLeaf = constructTree(parsedControlInput, size);
            }
        } else {
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



/**
* \fn char afficherArbre( NOEUD *noeud )
* \brief Fonction affichant rÃ©cursivement les noeuds de l'arbre de droite Ã  gauche
* \param noeud La racine de l'arbre Ã  afficher sur la sortie standard
* \return La valeur du noeud lu (avant appels recursifs sur ses noeuds fils)
*/
char* displayTree( node* noeud ){
    if ( noeud != NULL ){
        printf("\t\tNoeud..................... [%s]\n", noeud->value);
        printf("\t\t\tFils gauche du noeud [%s].. [%s]\n", noeud->value, displayTree(noeud->left));
        printf("\t\t\tFils droit  du noeud [%s].. [%s]\n", noeud->value, displayTree(noeud->right));
        return noeud->value;
    }
    return "nobody";
}
