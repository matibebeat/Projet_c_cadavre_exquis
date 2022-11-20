#ifndef UNTITLED_MANAGESTR_H
#define UNTITLED_MANAGESTR_H

char **split(char *string, char delimiter);
int countSplit(char *string, char delimiter);
void displayListOfStr(char **listOfStr, int size);
char *joinStrings(char *strings[], char *seperator, int count);
#endif //UNTITLED_MANAGESTR_H