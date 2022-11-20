#ifndef UNTITLED_VARIANT_H
#define UNTITLED_VARIANT_H
#include "Node.h"
static int BASE_NUMBER = 1;
static int BASE_GENRE = 4;
enum WORD_TYPES
{//all the words used in the genrator
  Noun,
  Verb,
  Adv,
  Adj,
  Pronoun,
  Preposition,
  Det,
  Other,
  Qui,
  Et,
  Stop
};

enum DECLINATION_PLURAL
{//all the number possible
  SG = 1,
  PL = 2,
  InvPL = 3
};

enum DECLINATION_GENRE
{//all the gender possible
  Mas = 4,
  Fem = 8,
  InvGen = 12
};
enum DECLINATION_PERSON
{//all the person possible
  P1 = 16,
  P2 = 32,
  P3 = 64
};
enum DECLINATION_TENSE
{//all the tense possible
  Inf = 128,
  IPre = 256,
  IImp = 512,
  SPre = 1024,
  IPSim = 2048,
  IFut = 4096,
  ImPre = 8192,
  Imp = 16384,
  SImp = 32768,
  PPas = 65536,
  PPre = 131072,
  CPre = 262144,
};

typedef struct variant
{
  int variantFlag;//the flag of the variant, it is the sum of all the attributes , for exemple if the variant is a plural masculine first person it will be 6
  /*
  We consider this integer as a binary number, each bit represent an attribute of the variant
  We use the following system to represent the variant:
    -we put all bits to 0
    -we put the bit corresponding to the attributes of the word to 1(singular, masculine, first person,tense,etc)
    -we take the decimal value of the binary number
  for exemple:
    if we take the word "chat" it's a masculine singular noun:
      - we put all the bits to 0 for intialisation 
      - the bit 1 is 1 because the word is singular
      - the bit 3 is 1 because the word is masculine
      so the binary number is 101 and the decimal number is 5, so the variantFlag is 5
    if the word is "a", it's a 3th person singular present indicative verb:
      - we put all the bits to 0 for intialisation 
      - the bit 1 is 1 because the word is singular
      - the bit 7 is 1 because the word is 3th person(P3)
      - the bit 9 is 1 because the word is present indicative(IPre)
      so the binary number is 101000001 and the decimal number is 321, so the variantFlag is 321
  */
  char *variantString;
  struct variant *next;
} variant;

void addVariant(tNode *node, int variantFlag, char *variantString);
int variantFlagToInt(char *subflag);
int getGenre(int variantFlag);
char *getGenreName(int genre);
int getPerson(int variantFlag);
char *getPersonName(int person);
int getPlural(int variantFlag);
char *getPluralName(int number);
char *getWordTypeName(int wordType);
int getTense(int variantFlag);
char *getTenseName(int tense);
#endif //UNTITLED_VARIANT_H