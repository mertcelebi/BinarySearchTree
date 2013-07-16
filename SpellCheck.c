/* Program Name: Spell13.c
   Program Description: Spell13 is a program that can 
   be used to check for spelling errors(among other things).
   Spell13.c uses a balanced BST to implement a dictionary.
   -----------
   Written by: Feridun Mert Celebi
   Date = 04/27/2013
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "/c/cs223/Hwk3/getLine.h"
#include "bst.h"

#define DIE(msg) exit (fprintf (stderr, "%s\n", msg)) //Prints out a single line of error message and exits.

//Function declarations.
void readLine(BST *tree, char *file, int balanceFactor, bool action);
void readWord(BST *tree, char *line, int balanceFactor, int length, bool action);
void editLine(char **line, int length);
char *appendCharacter(char *word, char toAdd, int length);

int main (int argc, char *argv[]){

  BST tree = createT(); //BST to be used.
	int balanceFactor = 1, i = 1;
	bool bfFlag = false;

	if ((!strcmp(argv[i], "-bf")) && (i + 1 != argc)){

		for (int checker = 0; checker < strlen(argv[i + 1]); checker++){

			if (!isdigit(argv[i + 1][checker])) DIE("Invalid balance factor.");
		}

		balanceFactor = atoi(argv[i + 1]);
		bfFlag = true;
	}

	if (balanceFactor <= 0) DIE("Invalid balance factor.");

	if (bfFlag) i = i + 2; //Balance factor is present and legitimate.

	//Goes through the command-line arguments.
	for (; i < argc; i++){

		if (!strcmp(argv[i], "-print")) inorderT(tree);

		else if (!strcmp(argv[i], "-dump")) preorderT(tree);

		else if (!strcmp(argv[i], "-stats")) printf("N = %d, H = %d, IPL = %d\n", sizeT(tree), heightT(tree), iplT(tree, 0));

		else if ((!strcmp(argv[i], "-d")) && (i + 1 != argc)) readLine(&tree, argv[++i], balanceFactor, false); //false to determine deletion.

		else readLine(&tree, argv[i], balanceFactor, true); //true to determine insertion.
	}

	tree = destroyT(tree);
	return EXIT_SUCCESS;
}

//Receives a pointer to the BST, the file name, balance factor and the boolean
//variable action which determines whether the process is an insertion (true) 
//or deletion (false).
//Reads the given file line by line and exits the program in case of an illegal
//file. Returns void.
void readLine(BST *tree, char *file, int balanceFactor, bool action){

	char *line;
	
	if (!strcmp(file, "-")){ //Read from standard input.

		while ((line = getLine(stdin))) readWord(tree, line, balanceFactor, strlen(line), action);
	}

	else{ //Read from a file.

		FILE *fileRead;
		fileRead = fopen(file, "r");

		if (!fileRead) DIE("Nonexistent file");

		while ((line = getLine(fileRead))) readWord(tree, line, balanceFactor, strlen(line), action);

		fclose(fileRead);
	}
}

//Receives a pointer to the BST, the line to be read, balance factor and the boolean
//variable action which determines whether the process is an insertion (true) 
//or deletion (false).
//Goes through the given line character by character, takes the lowercase of them
//and seperates the line to its words depending on the presence of non-alphanumeric
//characters and then either adds/deletes the word to/from the BST.
//Returns void.
void readWord(BST *tree, char *line, int balanceFactor, int length, bool action){

	int index = 0;
	char *word = strdup("");

	while (index < length){

		if ((!isalpha(line[index])) && (!isdigit(line[index]))){

			if (!strcmp(word, "")) {

				index++;
				continue;
			}
			if (action) (*tree) = insertT(*tree, word, balanceFactor);
			else (*tree) = deleteT(*tree, word, balanceFactor);

			word = strdup("");
		}

		else word = appendCharacter(word, tolower(line[index]), strlen(word)); //Lower case covered.
		
		index++;
	}
}

//Receives a pointer to a string and a character.
//Adds the character to the end of the given word.
//Returns void.
char *appendCharacter(char *word, char toAdd, int length){

	char *toModify = malloc(length + 2);
	strcpy(toModify, word);
	toModify[length] = toAdd;
	toModify[length + 1] = '\0';
	return toModify;
}
