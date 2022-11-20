#include "LinkedList.h"
#include "Variant.h"
#include <stdio.h>
void display(variant *root)
{
  if (root == NULL)
  {
    return;
  }
  printf(" -> %s", root->variantString);
  display(root->next);
}

variant *createLinkedList(int variantFlag, char *variantString)
{
  variant *list = malloc(sizeof(variant));
  list->variantFlag = variantFlag;
  list->variantString = variantString;
  list->next = NULL;
  return list;
}
void appendToList(variant *root, int variantFlag, char *variantString)
{
  if (root == NULL)
  {
    return;
  }
  while (root->next != NULL)//we search the end of the list
  {
    root = root->next;
  }
  root->next = createLinkedList(variantFlag, variantString);
}
char *reverseLinkedList(variant *var)
{
  // a function that reverses the linked list into a string
  int length = 0;
  variant *tmp = var;
  while (tmp != NULL)//search for the lenght of the list
  {
    length++;
    tmp = tmp->next;
  }

  char *str = malloc(length * sizeof(char));
  int i = 0;
  while (var != NULL)//we reverse the letter of the word
  {
    str[length - i - 1] = *var->variantString;
    var = var->next;
    i++;
  }
  str[length - 1] = '\0';
  return str;
}