// traversals.h
#ifndef TRAVERSALS_H
#define TRAVERSALS_H

void traverseLevelOrder(node_t*, const char[]);
void traverseCurrentLevel(node_t*, int, FILE *);
void traversePreOrder(node_t*, const char[]);
void traverseInOrder(node_t*, const char[]);
int getHeight(node_t*);

#endif
