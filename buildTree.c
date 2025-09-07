//buildTree.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "node.h"
#include "buildTree.h"

/* This function will initialize and return a new binary search tree. */
node_t* newNode(const char key, const char * word) {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->left = NULL;
        temp->right = NULL;

	temp->key = key;
	strcpy(temp->string, word);

	return temp;
}

/* This function will check if a binary search tree exists. It will create
 * a tree if it does not before comparing keys and inserting data into the nodes. */
node_t* insert(node_t* root, const char key, const char * word) {
	/* If the node is empty, create a new node */
	if (root == NULL) {
		return newNode(key, word);
	}

	/* If the key is the same as the key in the node, append a space and the string to node */
	if (key == root->key) {
		strcat(root->string, " ");
		strcat(root->string, word);
		return root;
	}
	
	/* If the key is less than or greater than the key in the node, recursively call insert */
	if (key < root->key) {
		root->left = insert(root->left, key, word);
	}
	else if (key > root->key){
		root->right = insert(root->right, key, word);
	}

	return root;
}

/* This function will build a binary search tree using the input file from the main driver. */
node_t* buildTree(FILE *input) {
	node_t* root = NULL;
	char word[100];
	while (fscanf(input, "%s", word) !=EOF)
	{
		int wordCount = 0;
		wordCount = strlen(word);
		char lastCh = word[wordCount - 1];
		/* Validate if string islower */
		int i;
		int isError = -1;
		int upperFlag = 0;
		int digitFlag = 0;
		int specialFlag = 0;
		for (i = 0; i < wordCount; i++) {
			if (!islower(word[i])) {
				if (isupper(word[i]) && upperFlag == 0) {
				 	printf("ERROR: Source file contains an upper case letter.\n");
					isError = 1;
					upperFlag = 1;
				}
				if (isdigit(word[i]) && digitFlag == 0) {
					printf("ERROR: Source file contains a number.\n");
					isError = 1;
					digitFlag = 1;
				}
				if ((!isupper(word[i]) && !isdigit(word[i])) && specialFlag == 0) {
					printf("ERROR: Source file contains special characters.\n");
					isError = 1;
					specialFlag = 1;
				}
			}
		}
		if (isError == 1) {
			printf("Source file must only contain lower case letters.\n");
			printf("Exiting Program...\n");
			exit(1);
		}
		
		/* If no input error, insert word into binary search tree */
		root = insert(root, lastCh, word);
	}
	return root;
}
