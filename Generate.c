#include <stdio.h>
#include <stdlib.h>
#include "ManageStr.h"
#include "Generate.h"
#include "Variant.h"
#include "LinkedList.h"
#include "FindWord.h"
#include "MathsTools.h"
/**
 * @brief Search in the tree all the words corresponding to a flag 
 * 
 * @param root The adress of the root of the tree
 * @param flag The flag to search
 * @param list the list of the words found
 */
void getAllPossible(tNode *root, int flag, variant *list)
{
  if (root == NULL)
  {
    return;//if the root is null we return because we are at the end of a branch
  }

  for (variant *var = root->variant; var != NULL; var = var->next)//we search each variant of the node
  {
    if ((flag & var->variantFlag) == flag)//if the flag correspond, we add it in the linked list
    {
      appendToList(list, var->variantFlag, var->variantString);
    }
  }
  //we search recursivly in the next and sibling
  getAllPossible(root->sibling, flag, list);
  getAllPossible(root->next, flag, list);
}
/**
 * @brief find a random word in the tree corresponding to a flag 
 * 
 * @param root the adress of the root of the tree
 * @param flag the flag to search
 * @return variant* 
 */
variant *randomWordWithConstraint(tNode *root, int flag)
{
  variant *list = createLinkedList(0, "");
  getAllPossible(root, flag, list);//We search all the words corresponding to the contraint and we add them in a linked list

  int len = 0;
  variant *tmp = list;
  while (tmp != NULL) //we count the number of words found
  {
    len++;
    tmp = tmp->next;
  }

  if (len == 1)//if the list is empty we return NULL
  {
    display(list);
    printf("\nConstraint: %d - ", flag);
    binarySumFromInt(flag);
    printf("\n");
    printf(RED "Warning: no word found with this constraint.\n" RESET);
    return NULL;
  }

  int r = (rand() % len) + 1;//we choose a random number between 1 and the number of words found
  tmp = list;
  for (int i = 1; i < r; i++)//we go to the word corresponding to the random number
  {
    tmp = tmp->next;
  }

  return tmp;//we return the node of the word
}
/**
 * @brief return a radom tense for the verb
 * 
 * @return int 
 */
int randomTense()
{ // we choose a random tense and we return the flag corresponding
  int num = rand() % 9;
  switch (num)
  {
  case 0:
    return CPre;
  case 1:
    return IPre;
  case 2:
    return IImp;
  case 3:
    return SPre;
  case 4:
    return IPSim;
  case 5:
    return IFut;
  case 6:
    return SImp;
  case 7:
    return PPas;
  case 8:
    return PPre;
  }
}

/**
 * @brief generate a random sentence wich is not grammatically correct
 * 
 * @param roots 
 * @param model 
 * @return variant** 
 */
variant **generateBaseForm(tNode **roots, int *model)
{
  int lenModel = 0;//we count the number of words in the model
  while (model[lenModel] != Stop && lenModel < MAX_MODEL_LENGTH)
  {
    lenModel++;
  }

  if (lenModel == MAX_MODEL_LENGTH)//if the model is too long we return null and we print an error message
  {
    printf(RED "Error: model too long or missing STOP.\n" RESET);
    return NULL;
  }

  int i = 0;

  int genreNumberConstraint = 0;
  int tenseConstraint = randomTense();//we choose a random tense for the sentence
  int personConstraint = 0;

  int passedVerb = 0;
  variant **baseForm = malloc(lenModel * sizeof(char *));
  while (model[i] != Stop)
  {//we loop for eaxh word in the model
    switch (model[i])
    {
    case Noun://if the word is a noun
      if (passedVerb && genreNumberConstraint || (passedVerb == 0 && genreNumberConstraint == 0))
      {//if we already passed a verb and we have a genreNumberConstraint or if we didn't passed a verb and we don't have a genreNumberConstraint we delete the gender constraint
        genreNumberConstraint = 0;
      }
      else
      {//we take a new gender constraint
        genreNumberConstraint = rand() % 4;
      }
      {//we put the constraint int the contraint
        passedVerb = 0;
        genreNumberConstraint = (1 + rand() % 2) * BASE_GENRE + (1 + rand() % 2) * BASE_NUMBER;
      }
      personConstraint = P3;
      baseForm[i] = randomWordWithConstraint(roots[Noun], genreNumberConstraint);//we search a random word corresponding to the constraint
      break;

    case Verb://if the word is a verb
      baseForm[i] = randomWordWithConstraint(roots[Verb], tenseConstraint + personConstraint + genreNumberConstraint);
      break;//we search a random verb wich can be conjugated with the constraint

    case Adv://if the wpord is an adverb
      baseForm[i] = randomWordWithConstraint(roots[Adv], 0);
      break;// an adverb is not conjugated so we don't need a constraint, we take a random one

    case Preposition://if the word is a preposition
      baseForm[i] = randomWordWithConstraint(roots[Preposition], 0);
      break;// a preposition is not conjugated so we don't need a constraint, we take a random one

    case Adj://if the word is an adjective
      baseForm[i] = randomWordWithConstraint(roots[Adj], genreNumberConstraint);
      break;// we take a random adjective corresponding to the gender and number constraint

    case Pronoun://if the word is a pronoun
      genreNumberConstraint = (1 + rand() % 2) * BASE_GENRE + (1 + rand() % 2) * BASE_NUMBER;//we recalculate a new flag with random constraints
      int randPerson = rand() % 3;//we choose a random person
      switch (randPerson)
      {
      case 0:
        personConstraint = P1;
        break;
      case 1:
        personConstraint = P2;
        break;
      case 2:
        personConstraint = P3;
        break;
      }
      baseForm[i] = randomWordWithConstraint(roots[Pronoun], personConstraint + genreNumberConstraint);//we search the good pronoun for those constraints
      break;

    case Qui://we put the word "qui" in the sentence
      baseForm[i] = createLinkedList(0, "qui");
      break;

    case Et://we put the word "et" in the sentence
      baseForm[i] = createLinkedList(0, "et");
      break;
    }
    i++;
  }
  return baseForm;//we return the list of vaiants of the sentence
}
/**
 * @brief adapt the baseform to be grammatically correct and add derterminants
 * 
 * @param baseForm 
 * @param rootDet 
 * @param model 
 * @return char* 
 */
char *generateFullForm(variant **baseForm, tNode *rootDet, int *model)
{
  int lenModel = 0;
  int fullLenModel = 0;
  while (model[lenModel] != Stop && lenModel < MAX_MODEL_LENGTH)
  {//we count the number of words in the model
    if (model[lenModel] == Noun)
    {
      fullLenModel++; // if the word is a noun we have to add a determiner before
    }
    lenModel++;
    fullLenModel++;
  }

  if (lenModel == MAX_MODEL_LENGTH)//if the model is too long we return null and we print an error message
  {
    printf(RED "Error: model too long or missing STOP.\n" RESET);
    return NULL;
  }

  int i = 0;
  int j = 0;
  char **fullForm = malloc(fullLenModel * sizeof(char *));
  while (model[j] != Stop)
  {
    if (model[j] == Noun)
    {
      int detFlag = 0;
      if (baseForm[j]->variantFlag % 4 != InvPL)//if the noun is not invariable, we add the number to the determiner constraint
      {
        detFlag += baseForm[j]->variantFlag % 4;
      }

      int genreFlag = ((baseForm[j]->variantFlag >> 2) << 2) % 16;//we add the genre to the determiner constraint if the noun is not invariable
      if (genreFlag != InvGen)
      {
        detFlag += genreFlag;
      }

      variant *det = randomWordWithConstraint(rootDet, baseForm[j] == NULL ? 0 : detFlag);//we search a determiner corresponding to the noun
      fullForm[i] = det == NULL ? "" : det->variantString;
      i++;
    }
    fullForm[i] = baseForm[j] == NULL ? "" : baseForm[j]->variantString;
    i++;
    j++;
  }

  return joinStrings(fullForm, " ", fullLenModel);//we return the sentence in a string
}


/**
 * @brief translate a model(list of int) and generate a sentence
 * 
 * @param model 
 * @param roots 
 * @return char* 
 */
char *getFullFormFromModel(int *model, tNode **roots)
{
  variant **baseForm = generateBaseForm(roots, model);//we generate the base form of the sentence
  char *fullForm = generateFullForm(baseForm, roots[Det], model);//we generate the full form of the sentence
  return fullForm;
}