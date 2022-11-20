#ifndef UNTITLED_FINDWORD_H
#define UNTITLED_FINDWORD_H
#include "Variant.h"
#define MAG "\x1B[35m"
#define RED "\x1B[31m"
#define RESET "\x1B[0m"

static int NB_WORD_TYPES = 8;

variant *findWord(tNode *root, char *word, variant *linkedList);
void describeWord(variant *var, int type, char *word);
void findAndDescribeWord(tNode **roots);
#endif //UNTITLED_FINDWORD_H