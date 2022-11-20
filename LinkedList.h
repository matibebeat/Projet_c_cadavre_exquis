#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H
#include "Variant.h"

void display(variant *root);
variant *createLinkedList(int variantFlag, char *variantString);
void appendToList(variant *root, int variantFlag, char *variantString);
char *reverseLinkedList(variant *var);
#endif //UNTITLED_LINKEDLIST_H
