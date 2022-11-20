#include <string.h>
/**
 * @brief cut the list with the delimiter and return them in a 2D array
 * 
 * @param string 
 * @param delimiter 
 * @return char** 
 */
char **split(char *string, char delimiter)
{
  char **result = 0;
  size_t count = 0;
  char *tmp = string;
  char *lastComma = 0;
  char delim[2];
  delim[0] = delimiter;
  delim[1] = 0;

  // count how many elements will be extracted
  while (*tmp)
  {
    if (delimiter == *tmp)
    {
      count++;
      lastComma = tmp;
    }
    tmp++;
  }

  // add space for trailing token
  count += lastComma < (string + strlen(string) - 1);

  // add space for terminating null string so caller
  // knows where the list of returned strings ends
  count++;

  result = malloc(sizeof(char *) * count);

  if (result)
  {
    size_t idx = 0;
    char *token = strtok(string, delim);

    while (token)
    {
      // assert(idx < count);
      *(result + idx++) = strdup(token);
      token = strtok(0, delim);
    }
    // assert(idx == count - 1);
    *(result + idx) = 0;
  }

  return result;
}
/**
 * @brief return the number of occurence of delimiter in a string and add 1 to it
 * 
 * @param string 
 * @param delimiter 
 * @return int 
 */
int countSplit(char *string, char delimiter)
{
  int len = strlen(string);
  int count = 0;
  for (int i = 0; i < len; i++)
  {
    if (string[i] == delimiter)
    {
      count++;
    }
  }
  return count + 1;// +1 because we have to count the last element
}
void displayListOfStr(char **listOfStr, int size)
{
  printf("%d strings\n", size);
  for (int i = 0; i < size; i++)
  {
    printf("%s ", listOfStr[i]);
  }
  printf("\n");
}

/**
 * @brief join two strings in one
 * 
 * @param strings 
 * @param seperator 
 * @param count 
 * @return char* 
 */
char *joinStrings(char *strings[], char *seperator, int count)
{
  char *str = NULL;       /* Pointer to the joined strings  */
  size_t totalLength = 0; /* Total length of joined strings */
  int i = 0;              /* Loop counter                   */

  /* Find total length of joined strings */
  for (i = 0; i < count; i++)
    totalLength += strlen(strings[i]);
  totalLength++;                                  /* For joined string terminator */
  totalLength += strlen(seperator) * (count - 1); // for seperators

  str = (char *)malloc(totalLength); /* Allocate memory for joined strings */
  str[0] = '\0';                     /* Empty string we can append to      */

  /* Append all the strings */
  for (i = 0; i < count; i++)
  {
    strcat(str, strings[i]);
    if (i < (count - 1))
      strcat(str, seperator);
  }

  return str;
}