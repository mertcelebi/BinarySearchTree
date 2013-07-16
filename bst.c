/* Program Name: bst.c
   Program Description: Complete implementation of
   a self-balanced BST.
   The basis of this code is taken by Prof. Stanley
   Eisenstat. Several changes are made to cover the 
   specific needs of the problem set.
   Besides Prof. Stan Eisenstat's code, I used online source
   to guide me while implementing certain operations.
   None of the code is copied. The code is only used as a
   guide.
   http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
   -----------
   Written by: Feridun Mert Celebi
   Date = 04/27/2013
*/

#define _GNU_SOURCE                     // Define strdup()
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "bst.h"

#define MAX(a,b) (((a)>(b))?(a):(b)) //Returns the higher of the two numbers.

//Tree data structure.
struct node {
    
    char *word; //Key stored at node.
    int height; //Height of tree at a given node.
    BST L, R; //Left and right children.
};

//Recalibrates the height of the given node.
//Returns that node.
static BST fixHeight(BST tree){

    if (!tree) return tree;

    tree -> height = MAX(heightT(tree -> L), heightT(tree -> R)) + 1;
    return tree;
}

//Applies a right rotation at the give node.
//Returns the modifed tree.
static BST rightRotate(BST tree){

    BST left = tree -> L, temp = left -> R;

    //Rotation is handled.
    left -> R = tree;
    tree -> L = temp;

    tree = fixHeight(tree);
    return fixHeight(left);
}

//Applies a left rotation at the give node.
//Returns the modifed tree.
static BST leftRotate(BST tree){

    BST right = tree -> R, temp = right -> L;

    //Rotation is handled.
    right -> L = tree;
    tree -> R = temp;

    tree = fixHeight(tree);
    return fixHeight(right);
}

//Return a one-element tree that contains the string S.
static BST makeNode(char *toAdd){

    BST tree = malloc (sizeof(*tree));
    tree -> word = strdup(toAdd);
    tree -> L = NULL;
    tree -> R = NULL;
    tree -> height = 0;
    return tree;
}

//Return an empty tree.
BST createT(void){

    return NULL;
}

//Destroy tree T; return NULL.
BST destroyT(BST tree){

    if (tree == NULL) return NULL;
    
    tree -> L = destroyT(tree -> L);
    tree -> R = destroyT(tree -> R);
    free(tree -> word);
    free(tree);
    return NULL;
}

//Receives the tree, string toAdd and the balanceFactor.
//Insert string S in T; return the modified T
//In the case of duplicates nothing is done.
BST insertT(BST tree, char *toAdd, int balanceFactor){

    if (tree == NULL) return makeNode(toAdd);
    
    else if (strcmp(toAdd, tree -> word) < 0) tree -> L = insertT(tree -> L, toAdd, balanceFactor);

    else if (strcmp(toAdd, tree -> word) > 0) tree -> R = insertT(tree -> R, toAdd, balanceFactor);

    else ; //Ignore duplicates.

    tree = fixHeight(tree);
    
    //Balancing starts
    int currentBalance = heightT(tree -> L) - heightT(tree -> R);

    if ((currentBalance > balanceFactor) && (strcmp(toAdd, (tree -> L -> word)) < 0)) return rightRotate(tree); //Left-left case.

    if ((currentBalance < (-1 * balanceFactor)) && (strcmp(toAdd, (tree -> R -> word)) > 0)) return leftRotate(tree); //Right-right case.
    
    if ((currentBalance > balanceFactor) && (strcmp(toAdd, (tree -> L -> word)) > 0)){ //Left-right case.

        tree -> L = leftRotate(tree -> L);
        return rightRotate(tree);
    }  
    
    if ((currentBalance < (-1 * balanceFactor)) && (strcmp(toAdd, (tree -> R -> word)) < 0)){ //Right-left case.

        tree -> R = rightRotate(tree -> R);
        return leftRotate(tree);
    }

    return tree;
}

//Set *P to largest node in T and delete that node; return modified T.
static BST deleteLargest(BST tree){

    BST p = tree; 
    
    while (p -> R) p = p -> R; 
    return p; 
}

//Receives the tree, string toDelete and the balanceFactor.
//Delete string toDelete from T (if it exists) and return modified tree.
//In the case of toDelete does not exist, the tree is returned.
BST deleteT(BST tree, char *toDelete, int balanceFactor){

    int currentBalance, childBalance;
    if (tree == NULL) return tree; //Tree is empty.
    
    else if (strcmp(toDelete, tree -> word) < 0){
     
       tree -> L = deleteT(tree -> L, toDelete, balanceFactor); //Delete from left subtree.
    } 

    else if (strcmp(tree -> word, toDelete) < 0){
	
       tree -> R = deleteT(tree -> R, toDelete, balanceFactor); //Delete from right subtree.
    } 

    else{ //Delete root modified.

        BST p; 
 
        if ((!(tree -> L)) && (!(tree -> R))){ //Case 1: No children.
            
            p = tree; 
            tree = NULL; 
        } 

        else if (!(tree->L)) tree = tree -> R; //Case 2: No left child.

        else if (!(tree -> R)) tree = tree -> L; //Case 3: No right child.

        else{ //Case 4: Two children.

            p = deleteLargest(tree -> L); 
            tree -> word = p -> word;
            tree -> L = deleteT(tree -> L, p -> word, balanceFactor); 
        }
    }

    //Rebalancing starts.
    if (!tree) return tree;

    tree = fixHeight(tree);

    currentBalance = heightT(tree -> L) - heightT(tree -> R);

    if (currentBalance > balanceFactor){

        childBalance = heightT(tree -> L -> L) - heightT(tree -> L -> R);

        if (childBalance >= 0) return rightRotate(tree); //Left-left case.

        else{ //Left-right case.

            tree -> L = leftRotate(tree -> L);
            return rightRotate(tree);
        }
    }

    else if (currentBalance < (-1 * balanceFactor)){

        childBalance = heightT(tree -> R -> L) - heightT(tree -> R -> R);

        if (childBalance <= 0) return leftRotate(tree); //Right-right case.

        else{ //Right-left case.

            tree -> R = rightRotate(tree -> R);
            return leftRotate(tree);
        }
    }

    return tree;
}

//Print keys in T in preorder, one per line.
void preorderT(BST tree){

    if (tree == NULL) return;

    printf("%s\n", tree -> word);
    preorderT(tree -> L);
    preorderT(tree -> R);
}

//Print keys in T in inorder, one per line.
void inorderT(BST tree){

    if (tree == NULL) return;
    
    inorderT(tree -> L);
    printf("%s\n", tree -> word);
    inorderT(tree -> R);
}

//Return number of nodes in T.
int sizeT(BST tree){

    if (!tree) return 0;
    else return sizeT(tree -> L) + sizeT(tree -> R) + 1;                           
}

//Return height of T
//Return -1, if tree is empty.
int heightT(BST tree){

    if (!tree) return -1;
    return tree -> height;  
}

//Return internal path length of T.
int iplT (BST tree, int sum){

    if (!tree) return 0;
    return sum + iplT(tree -> R, sum + 1) + iplT(tree -> L, sum + 1);
}
