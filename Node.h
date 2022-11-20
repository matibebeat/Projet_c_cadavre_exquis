#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

typedef struct sNode
{
  char letter;
  struct sNode *sibling;
  struct sNode *next;
  struct variant *variant;
} tNode;

tNode *createNode(char letter);

#endif //UNTITLED_NODE_H