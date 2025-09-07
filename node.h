// node.h
#ifndef NODE_H
#define NODE_H

typedef struct node {
	char key;
 	char string[100];

	struct node *left;
	struct node *right;
} node_t;

#endif
