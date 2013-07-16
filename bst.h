/* Program Name: bst.h
   Program Description: Complete interface of
   a self-balanced BST.
   The basis of this code is taken by Prof. Stanley
   Eisenstat. Several changes are made to cover the 
   specific needs of the problem set.
   -----------
   Written by: Feridun Mert Celebi
   Date = 04/27/2013
*/

#include <stdio.h>
#include <math.h>

//Tree data structure
//A variable of type BST is a pointer to the struct used to implement the
//BST operations declared below.  Note that the declaration of that struct
//appears only in the file that implements these operations.  Thus the calling
//program does not know what fields have been defined and cannot access them;
//and the variable must be a pointer since the size of the struct is unknown.
typedef struct node *BST;

//Return an empty tree
BST createT(void);

//Destroy the BST by freeing any storage that it uses
//Destroy tree; return NULL
BST destroyT(BST tree);

//Receives the tree, string toAdd and the balanceFactor.
//Insert string S in T; return the modified T
//In the case of duplicates nothing is done.
BST insertT(BST tree, char *toAdd, int balanceFactor);

//Receives the tree, string toDelete and the balanceFactor.
//Delete string toDelete from T (if it exists) and return modified tree.
//In the case of toDelete does not exist, the tree is returned.
BST deleteT(BST tree, char *toDelete, int balanceFactor);

//Print keys in T in preorder, one per line
void preorderT(BST tree);

//Print keys in T in inorder, one per line
void inorderT(BST tree);

//Return number of nodes in T
int sizeT(BST tree);

//Return height of T
//Return -1, if tree is empty.
int heightT(BST tree);

//Return internal path length of T
int iplT(BST tree, int sum);
