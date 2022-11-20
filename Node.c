#include "Node.h"
#include <stdio.h>

/**
 * @brief Create a Node object and initiate all pointers to NULL
 * 
 * @param letter The letter inside the node
 * @return tNode* 
 */
tNode *createNode(char letter)
{
  tNode *newNode;
  newNode = (tNode *)malloc(sizeof(tNode));
  newNode->letter = letter;
  newNode->sibling = NULL;
  newNode->next = NULL;
  newNode->variant = NULL;
  return newNode;
}