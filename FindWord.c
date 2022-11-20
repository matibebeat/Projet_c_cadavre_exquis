#include "Variant.h"
#include "FindWord.h"
#include "LinkedList.h"
#include <stdio.h>
#include <string.h>
/**
 * @brief find the variant wich correspond to word in the tree
 * 
 * @param root the tree where the word should be
 * @param word the word to find
 * @param linkedList 
 * @return variant* 
 */
variant *findWord(tNode *root, char *word, variant *linkedList)
{
  if (root == NULL)//we are at the end of a branch and the word is not found in the branch
  {
    return NULL;
  }

  variant *var = root->variant;
  while (var != NULL)
  {//we search if there is a variant with the same word in the node and we put it in the linked list and we return it
    if (strcmp(var->variantString, word) == 0)
    {
      appendToList(linkedList, 0, &(root->letter));
      return var;
    }
    var = var->next;
  }
  //we search recursivly in the next and if it exist we add it in the linked list
  variant *found1 = findWord(root->next, word, linkedList);
  if (found1 != NULL)
  {
    appendToList(linkedList, 0, &(root->letter));
    return found1;
  }
  //we search recursivly in the sibling and if it exist we add it in the linked list
  variant *found2 = findWord(root->sibling, word, linkedList);
  if (found2 != NULL)
  {
    return found2;
  }

  return NULL;
}
/**
 * @brief take a word and describe it 
 * 
 * @param var 
 * @param type 
 * @param word 
 */
void describeWord(variant *var, int type, char *word)
{
  if (var == NULL)
  {
    printf(RED "Error: word not found.\n" RESET);
    return;
  }

  char *wordType = getWordTypeName(type);

  if (strcmp(wordType, "verbe") == 0)
  {//if the word is a verb we display the attributes of the verb (tense, person, number, mood)
    char *tense = getTenseName(getTense(var->variantFlag));
    if (strcmp(tense, "infinitif") == 0)
    {
      printf("%s: %s %s, infinitif\n", var->variantString, wordType, word);
    }
    else
    {
      printf("%s: %s %s, %s du %s, %s\n", var->variantString, wordType, word, getPersonName(getPerson(var->variantFlag)), getPluralName(getPlural(var->variantFlag)), getTenseName(getTense(var->variantFlag)));
    }
  }
  else if (strcmp(wordType, "nom") == 0 || strcmp(wordType, "déterminant") == 0 || strcmp(wordType, "adjectif") == 0)//if the word is a noun,an adjectiv or a determinant we display the attributes of it
  {
    printf("%s: %s %s, %s, %s\n", var->variantString, wordType, word, getGenreName(getGenre(var->variantFlag)), getPluralName(getPlural(var->variantFlag)));
  }
  else
  {//else the word is invariable, ther is no attributes to display  
    printf("%s: %s %s\n", var->variantString, wordType, word);
  }
}
/**
 * @brief find the word in the tree and describe it
 * 
 * @param roots 
 */
void findAndDescribeWord(tNode **roots)
{
  char word[100];
  printf("Enter a word: ");
  scanf("%s", word);

  for (int i = 0; i < NB_WORD_TYPES; i++)
  {
    variant *v = createLinkedList(0, "");//we create a linked list to store the path to all the variant corresponding to the word
    variant *found = findWord(roots[i], word, v);//we search all the variant corresponding to the word
    char *word = reverseLinkedList(v);// we reverse the linked list to get the path to the variant

    if (found != NULL)
    {
      describeWord(found, i, word);//we describe the variant
      return;
    }
  }

  printf(MAG "Word not found!\n" RESET);
}