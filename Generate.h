#ifndef UNTITLED_GENERATE_H
#define UNTITLED_GENERATE_H
#include "Node.h"
#include "Variant.h"
#define RED "\x1B[31m"
#define RESET "\x1B[0m"
static int MAX_MODEL_LENGTH=16;
void getAllPossible(tNode *root, int flag, variant *list);
variant *randomWordWithConstraint(tNode *root, int flag);
int randomTense();
variant **generateBaseForm(tNode **roots, int *model);
char *generateFullForm(variant **baseForm, tNode *rootDet, int *model);
char *getFullFormFromModel(int *model, tNode **roots);
#endif //UNTITLED_GENERATE_H