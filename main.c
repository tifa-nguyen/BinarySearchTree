//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "node.h"
#include "traversals.h"
#include "buildTree.h"

void help(char* []);

int main(int argc, char* argv[]) {
	int option;
	const int SIZE = 1000;
	FILE *fptr;
	FILE *ftemp;
	char buffer[SIZE];
	char *fileName;
	char *fileTemp = "tempFile";
	char *fileLevelOrder = NULL;
	char *filePreOrder = NULL;
	char *fileInOrder = NULL;
	
	/* Switch Case for getopt */
	while ((option = getopt(argc, argv, "h")) != -1) {
		switch(option) {
		case 'h':
			help(argv);
			break;
		case '?':
			printf("Invalid option. Type %s -h for usage help.\n", argv[0]);
			exit(1);
		default:
			break;
		}
	}

	/* Create empty node_t called root */
	node_t *root = NULL;

	/* Check if program call is using appropriate usage and if command line call, file redirect, or keyboard input for filename */
	if (argc >= 3) {	// If there are more than 2 arguments for program name and input file, print usage error and terminate
		printf("Fatal: Improper usage\n");
		printf("Usage: %s [filename]\n\n", argv[0]);
		exit(1);
	}
	if (argc == 2) {	// If 2 arguments, open filename from argv[1] and create node.
		fptr = fopen(argv[1], "r");
		fileName = argv[1];
		root = buildTree(fptr);
		fclose(fptr);
	}
	else if (argc == 1) {	// If 1 argument, get input from stdin
		do {
			scanf("%s", buffer);
		} while (feof(stdin));

		/* Create temporary file with contents of buffer */
		ftemp = fopen(fileTemp, "w");
		fprintf(ftemp, "%s", buffer);
		fclose(ftemp);

		if ((fptr = fopen(buffer, "r")) != NULL) {	// If the string from buffer is a filename, open file and create tree
			fileName = "out";
			root = buildTree(fptr);
			fclose(fptr);
		}
		else {		// If the string from buffer is not a filename, take stdin as fptr and append to ftemp due to buffer reading first word of stdin redirect
			fptr = stdin;
			fileName = "out";
			ftemp = fopen(fileTemp, "a");
			char c = fgetc(fptr);
			while (c != EOF) {
				fputc(c, ftemp);
				c = fgetc(fptr);
			}
			fclose(ftemp);
			fclose(fptr);
			ftemp = fopen(fileTemp, "r");
			root = buildTree(ftemp);
			fclose(ftemp);
			remove(fileTemp);
		}
	}

	/* If fptr is empty, print error */
	if (fptr == NULL) {
		printf("\n\nERROR: The file could not be read.\n");
		printf("       Exiting Program.\n\n");
		exit(1);
	}

	/* Initialize output filename suffixies */
	int filelength = strlen(fileName);
	fileLevelOrder = malloc(filelength);
	filePreOrder = malloc(filelength);
	fileInOrder = malloc(filelength);
	char *suffixLevelOrder = ".levelorder";
	char *suffixPreOrder = ".preorder";
	char *suffixInOrder = ".inorder";

	/* Create output filenames with appropriate suffixes */
	strcpy(fileLevelOrder, fileName);
	strcat(fileLevelOrder, suffixLevelOrder);
	strcpy(filePreOrder, fileName);
	strcat(filePreOrder, suffixPreOrder);
	strcpy(fileInOrder, fileName);
	strcat(fileInOrder, suffixInOrder);

	/* Calls to traverse binary search tree */
	printf("Traversing tree with level order traversal.\n");
	traverseLevelOrder(root, fileLevelOrder);
	printf("Printing result to %s.\n", fileLevelOrder);
	printf("Traversing tree with preorder traversal.\n");
	traversePreOrder(root, filePreOrder);
	printf("Printing result to %s.\n", filePreOrder);
	printf("Traversing tree with in-order traversal.\n");
	traverseInOrder(root, fileInOrder);
	printf("Printing result to %s.\n", fileInOrder);
	
	printf("Exiting program.\n");

	return 0;
}

/* This function prints the help message if the help option is used during program execution. */
void help(char* argv[]) {
	printf("Usage:\n");
	printf("   %s [filename]", argv[0]);
	printf("\nOptions:\n");
	printf("   -h     display help message and exit\n");
	printf("\nfilename  optional source filename to read data from\n\n");
	exit(0);
}
