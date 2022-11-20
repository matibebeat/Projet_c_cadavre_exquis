#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H
#include "Node.h"
#define MAG "\x1B[35m"
#define RED "\x1B[31m"
#define CYN "\x1B[36m"
#define RESET "\x1B[0m"


void menu(tNode **roots);
int getUserInput(int min, int max, char *message);
void displayModel(int *model, int modelSize);
int *customModel();
#endif //UNTITLED_MENU_H