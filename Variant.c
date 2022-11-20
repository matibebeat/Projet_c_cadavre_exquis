#include "Variant.h"
#include "Node.h"
#include <stdio.h>


/**
 * @brief Create a Variant object and put it inside the node
 * 
 * @param node The node where the variant will be put
 * @param variantString The string of the variant
 * @param variantFlag The flag of the variant
 */
void addVariant(tNode *node, int variantFlag, char *variantString)
{
  variant *newVariant = (variant *)malloc(sizeof(variant));//create a node for the variant
  newVariant->variantFlag = variantFlag;
  newVariant->variantString = variantString;
  newVariant->next = NULL;
  //search for the end of the variant list
  if (node->variant == NULL)
  {
    node->variant = newVariant;
  }
  else//put the variant at the end of the list
  {
    variant *temp = node->variant;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newVariant;
  }

  return;
}
/**
 * @brief Translates the variant flag into an integer
 * 
 * @param subflag The string of the flag
 * @return int 
 */
int variantFlagToInt(char *subflag)
{
  int flag = 0;
  if (strstr(subflag, "Mas") == NULL && strstr(subflag, "Fem") == NULL && strstr(subflag, "InvGen") == NULL)
  {
    flag += InvGen;//si le genre n'est pas précisé, on met InvGen, CaD qu'on lui met feminin et masculin
  }

  if (strstr(subflag, "P1") == NULL && strstr(subflag, "P2") == NULL && strstr(subflag, "P3") == NULL)
  {
    flag += P1 + P2 + P3;//si la personne n'est pas précisée, on met P1, P2 et P3, CaD qu'on lui met 1ere, 2eme et 3eme personne
  }
  //we loop over all the attributes of the variant and add them to the flag
  int nbBits = countSplit(subflag, '+');
  char **bits = split(subflag, '+');
  for (int i = 0; i < nbBits; i++)
  {
    if (strcmp(bits[i], "SG") == 0)
    {
      flag += SG;
    }
    else if (strcmp(bits[i], "PL") == 0)
    {
      flag += PL;
    }
    else if (strcmp(bits[i], "Mas") == 0)
    {
      flag += Mas;
    }
    else if (strcmp(bits[i], "Fem") == 0)
    {
      flag += Fem;
    }
    else if (strcmp(bits[i], "P1") == 0)
    {
      flag += P1;
    }
    else if (strcmp(bits[i], "P2") == 0)
    {
      flag += P2;
    }
    else if (strcmp(bits[i], "P3") == 0)
    {
      flag += P3;
    }
    else if (strcmp(bits[i], "Inf") == 0)
    {
      flag += Inf;
    }
    else if (strcmp(bits[i], "IPre") == 0)
    {
      flag += IPre;
    }
    else if (strcmp(bits[i], "IImp") == 0)
    {
      flag += IImp;
    }
    else if (strcmp(bits[i], "SPre") == 0)
    {
      flag += SPre;
    }
    else if (strcmp(bits[i], "InvPL") == 0)
    {
      flag += InvPL;
    }
    else if (strcmp(bits[i], "InvGen") == 0)
    {
      flag += InvGen;
    }
    else if (strcmp(bits[i], "3Fem") == 0)
    {
      flag += P3 + Fem;
    }
    else if (strcmp(bits[i], "3Mas") == 0)
    {
      flag += P3 + Mas;
    }
    else if (strcmp(bits[i], "IPSim") == 0)
    {
      flag += IPSim;
    }
    else if (strcmp(bits[i], "IFut") == 0)
    {
      flag += IFut;
    }
    else if (strcmp(bits[i], "ImPre") == 0)
    {
      flag += ImPre;
    }
    else if (strcmp(bits[i], "Imp") == 0)
    {
      flag += Imp;
    }
    else if (strcmp(bits[i], "SImp") == 0)
    {
      flag += SImp;
    }
    else if (strcmp(bits[i], "SPre") == 0)
    {
      flag += SPre;
    }
    else if (strcmp(bits[i], "PPas") == 0)
    {
      flag += PPas;
    }
    else if (strcmp(bits[i], "PPre") == 0)
    {
      flag += PPre;
    }
    else if (strcmp(bits[i], "CPre") == 0)
    {
      flag += CPre;
    }
  }

  return flag;
}
/**
 * @brief Get the Genre with the flag
 * 
 * @param variantFlag The full flag of the variant
 * @return int the part of the flag that contains the genre
 */
int getGenre(int variantFlag)
{
  return ((variantFlag >> 2) % 4) << 2;//we return the bit corresponding to the genre
}
/**
 * @brief translate the flag into a string, for the gender
 * 
 * @param genre 
 * @return char* 
 */
char *getGenreName(int genre)
{
  char *genreName;
  switch (genre)
  {
  case Mas:
    genreName = "masculin";
    break;
  case Fem:
    genreName = "féminin";
    break;
  case InvGen:
    genreName = "invariable";
    break;
  }

  return genreName;
}
/**
 * @brief Get the Person with the flag
 * 
 * @param variantFlag The full flag of the variant
 * @return int int the part of the flag that contains the person
 */
int getPerson(int variantFlag)
{
  return ((variantFlag >> 4) % 8) << 4;//we return the bit corresponding to the person
}
/**
 * @brief translate the flag into a string, for the person
 * 
 * @param person 
 * @return char* 
 */
char *getPersonName(int person)
{
  char *personName;
  switch (person)
  {
  case P1:
    personName = "1ère personne";
    break;
  case P2:
    personName = "2ème personne";
    break;
  case P3:
    personName = "3ème personne";
    break;
  default:
    personName = "1ère personne, 2ème personne ou 3ème personne";
    break;
  }
  return personName;
}
/**
 * @brief Get the Plural with the flag
 * 
 * @param variantFlag The full flag of the variant
 * @return int the part of the flag that contains the plural
 */
int getPlural(int variantFlag)
{
  return variantFlag % 4;//we return the bit corresponding to the plural
}
/**
 * @brief translate the flag into a string, for the plural
 * 
 * @param number 
 * @return char* 
 */
char *getPluralName(int number)
{
  char *pluralName;
  switch (number)
  {
  case 1:
    pluralName = "singulier";
    break;
  case 2:
    pluralName = "pluriel";
    break;
  case 3:
    pluralName = "invariable";
    break;
  }
  return pluralName;
}
/**
 * @brief translate the wordtype into a string
 * 
 * @param wordType 
 * @return char* 
 */
char *getWordTypeName(int wordType)
{
  char *wordTypeName;
  switch (wordType)
  {
  case Verb:
    wordTypeName = "verbe";
    break;
  case Adj:
    wordTypeName = "adjectif";
    break;
  case Adv:
    wordTypeName = "adverbe";
    break;
  case Preposition:
    wordTypeName = "préposition";
    break;
  case Pronoun:
    wordTypeName = "pronom";
    break;
  case Noun:
    wordTypeName = "nom";
    break;
  case Det:
    wordTypeName = "déterminant";
    break;
  case Other:
    wordTypeName = "autre";
    break;
  case Qui:
    wordTypeName = "qui";
    break;
  case Et:
    wordTypeName = "et";
    break;
  case Stop:
    wordTypeName = "stop";
    break;
  default:
    wordTypeName = "inconnu";
    break;
  }
  return wordTypeName;
}
/**
 * @brief Get the tense with the flag
 * 
 * @param variantFlag the full flag of the variant
 * @return int the part of the flag that contains the tense
 */
int getTense(int variantFlag)
{
  return (variantFlag >> 7) << 7;//we return the bit corresponding to the tense
}
/**
 * @brief translate the flag into a string, for the tense
 * 
 * @param tense 
 * @return char* 
 */
char *getTenseName(int tense)
{
  char *tenseName;
  switch (tense)
  {
  case Imp:
    tenseName = "imparfait";
    break;
  case Inf:
    tenseName = "infinitif";
    break;
  case IPre:
    tenseName = "présent de l'indicatif";
    break;
  case IImp:
    tenseName = "imparfait de l'indicatif";
    break;
  case SPre:
    tenseName = "présent du subjonctif";
    break;
  case IFut:
    tenseName = "futur de l'indicatif";
    break;
  case ImPre:
    tenseName = "présent de l'inperatif";
    break;
  case SImp:
    tenseName = "imparfait du subjonctif";
    break;
  case PPas:
    tenseName = "participe passé";
    break;
  case PPre:
    tenseName = "participe présent";
    break;
  case CPre:
    tenseName = "conditionel présent";
    break;
  case IPSim:
    tenseName = "passé simple de l'indicatif";
    break;
  }
  return tenseName;
}
