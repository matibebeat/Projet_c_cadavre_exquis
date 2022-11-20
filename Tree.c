#include "Tree.h"
#include "Node.h"
#include "Variant.h"
#include <stdio.h>


/**
 * @brief Put the word "word" in the tree, the fonction is called recursively for each letter of the word
 * 
 * @param root The root of the tree where the word will be put
 * @param word The word to put in the tree
 * @param size The size of the word
 * @param flag The flag of the word
 * @param variantString The variant string of the word
 */
void putWordInTree(tNode *root, char *word, int size, int flag, char *variantString)
{
  int len = strlen(word) - size;
  if (size == 1)//if the letter is the last of the word we had a variant to the node, and we stop here
  {
    addVariant(findSibling(root, word[len], 1), flag, variantString);
    return;
  }
  //we search the sibling corresponding to the letter
  root = findSibling(root, word[len], 1);
  if (root->next == NULL)
  {//if the node doesn't have a next node, we create one
    root->next = createNode(word[len + 1]);
  }
  //we call the function for the next letter, with the next node and the next letter
  putWordInTree(root->next, word, size - 1, flag, variantString);

  return;
}

/**
 * @brief Fill trees with the words from the file
 * 
 * @param roots Adress of the table of all tree roots
 */
void treeFromDict(tNode **roots)
{
  //we open the file
  FILE *f = fopen("dico.txt", "r");
  //we create a buffer to read the file
  char buf[200];
  char *word, *variantString, *variantFlag;

  while (fgets(buf, sizeof buf, f) != NULL)
  {
    buf[strcspn(buf, "\n")] = 0;
    char **splitBuf = split(buf, '\t');
    char *variantString = splitBuf[0];
    char *word = splitBuf[1];
    char *variantFlag = splitBuf[2];    //we split the line into 3 parts, the variant string, the word and the variant flag

    tNode *root;

    int nbSubflags = countSplit(variantFlag, ':');
    char **subflags = split(variantFlag, ':');
    //we chek the type of the word and we put it in the right tree
    if (strcmp(subflags[0], "Ver") == 0)
    {
      root = roots[Verb];
    }
    else if (strcmp(subflags[0], "Nom") == 0)
    {
      root = roots[Noun];
    }
    else if (strcmp(subflags[0], "Det") == 0)
    {
      root = roots[Det];
    }
    else if (strcmp(subflags[0], "Adj") == 0)
    {
      root = roots[Adj];
    }
    else if (strcmp(subflags[0], "Adv") == 0)
    {
      root = roots[Adv];
    }
    else if (strcmp(subflags[0], "Pre") == 0)
    {
      root = roots[Preposition];
    }
    else if (strcmp(subflags[0], "Pro") == 0)
    {
      root = roots[Pronoun];
    }
    else
    {
      root = roots[Other];
    }
    //we put the word in the tree
    if (nbSubflags == 1)
    {
      putWordInTree(root, word, strlen(word), 0, variantString);
    }
    else{//if the word has a subflag, we put it in the tree and add a variant for each subflag
      for (int i = 1; i < nbSubflags; i++)
      {
        int flag = variantFlagToInt(subflags[i]);
        putWordInTree(root, word, strlen(word), flag, variantString);
      }
    }
  }
  return;
}
/**
 * @brief Find the sibling of the node with the letter "letter"
 * 
 * @param root The node where the search will start
 * @param letter The letter of the sibling to find
 * @param create If the sibling doesn't exist, create it
 * @return tNode* 
 */
tNode *findSibling(tNode *root, char letter, int createNewNode)
{
  tNode *temp = root;
  if (temp->letter == letter)
  {
    return temp;
  }
//we search the sibling corresponding to the letter
  while (temp->sibling != NULL)
  {
    temp = temp->sibling;
    if (temp->letter == letter)//if we find the sibling, we return it
    {
      return temp;
    }
  }

  if (createNewNode)//if the sibling doesn't exist,and createNewNode=1 ,we create it
  {
    temp->sibling = createNode(letter);
    return temp->sibling;
  }
  else
  {
    return NULL;//else we returnn null
  }
}



