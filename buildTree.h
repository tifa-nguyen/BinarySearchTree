// buildTree.h
#ifndef BUILDTREE_H
#define BUILDTREE_H

node_t* newNode(const char, const char *);
node_t* insert(node_t *, const char, const char *);
node_t* buildTree(FILE *);

#endif
