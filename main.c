#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Node.h"
#include "Variant.h"
#include "Generate.h"
#include "FindWord.h"
#include "Tree.h"
#include "Menu.h"



int main()
{
  srand(time(NULL));

  tNode **roots = malloc(NB_WORD_TYPES * sizeof(tNode *));
  // Initiate all roots to the letter a, for each type of word (noun, verb, adjective, adverb, preposition, pronoun, det, other(ex: interjection, abreavation))
  roots[Noun] = createNode('a');
  roots[Verb] = createNode('a');
  roots[Adv] = createNode('a');
  roots[Adj] = createNode('a');
  roots[Pronoun] = createNode('a');
  roots[Det] = createNode('a');
  roots[Preposition] = createNode('a');
  roots[Other] = createNode('a');
  //fill the trees with the words from the file
  treeFromDict(roots);
  //start the menu 
  menu(roots);

  return 0;
}