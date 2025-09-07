//traversals.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "traversals.h"

/* This function obtains the height of the binary search tree and calls for
 * the level order traversal of the current level of the tree. */
void traverseLevelOrder(node_t* root, const char *output) {
	if (root != NULL) {
		FILE *fptr;
		fptr = fopen(output, "a");
		int height = getHeight(root);
		int i;
		for (i = 1; i <= height; i++) {
			traverseCurrentLevel(root, i, fptr);
		}
		fclose(fptr);
	}
}

/* This function prints the contents of the node at the current level of the
 * tree's output. */
void traverseCurrentLevel(node_t* root, int level, FILE *fptr) {
	if (root == NULL) {
		return;
	}
		fprintf(fptr, "%*c%d: %c %s\n", level * 2, ' ', level, root->key, root->string);
		traverseCurrentLevel(root->left, level + 1, fptr);
		traverseCurrentLevel(root->right, level + 1, fptr);
}

/* This function traverses the binary search tree in a pre-order traversal of
 * root -> left child -> right child. */
void traversePreOrder(node_t* root, const char *output) {
	if (root != NULL) {
		FILE *fptr;
		fptr = fopen(output, "a");
		fprintf(fptr, "%c %s\n", root->key, root->string);
		fclose(fptr);
		traversePreOrder(root->left, output);
		traversePreOrder(root->right, output);
	}
}

/* This function traverses the binary search tree in a in-order traversal of
 * left child -> root -> right child. */
void traverseInOrder(node_t* root, const char *output) {
	if (root != NULL) {
		traverseInOrder(root->left, output);
		FILE *fptr;
		fptr = fopen(output, "a");
		fprintf(fptr, "%c %s\n", root->key, root->string);
		fclose(fptr);
		traverseInOrder(root->right, output);
	}
}

/* This function returns the height of the binary search tree. */
int getHeight(node_t* root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int left = getHeight(root->left);
		int right = getHeight(root->right);
		if (left > right) {
			return (left + 1);
		}
		else {
			return (right + 1);
		}
	}
}
