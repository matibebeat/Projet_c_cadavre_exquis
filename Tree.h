#ifndef UNTITLED_TREE_H
#define UNTITLED_TREE_H
#include "Node.h"


void putWordInTree(tNode *root, char *word, int size, int flag, char *variantString);
void treeFromDict(tNode **roots);
tNode *findSibling(tNode *root, char letter, int createNewNode);
#endif //UNTITLED_TREE_H