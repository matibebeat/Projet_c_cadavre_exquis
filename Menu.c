#include "Menu.h"
#include "Node.h"
#include "Variant.h"
#include "Generate.h"
#include "FindWord.h"
/**
 * @brief show the menu
 *
 * @param root Adress of the table of all tree roots
 */
void menu(tNode **roots)
{
  int action_choice = 0;
  // We inialize all of the basic models
  int model0[] = {Noun, Adj, Verb, Noun, Stop};
  int model1[] = {Noun, Qui, Verb, Verb, Noun, Stop};
  int model2[] = {Pronoun, Verb, Noun, Adj, Stop};
  int model3[] = {Noun, Et, Noun, Verb, Adv, Stop};

  // We iniate main messages
  char *welcomeMessage = MAG "\n\n              ════════════ ❀•°❀°•❀ ════════════\n"
                             " Welcome to CADAVRE EXQUIS 💀💀💀 What do you want to do?\n"
                             "              ════════════ ❀•°❀°•❀ ════════════\n\n"
                             " - Type 0 to generate a random sentence\n"
                             " - Type 1 to CREATE YOUR OWN MODEL (ONLY 9.99$/MONTH 😎) with a FREE trial\n"
                             " - Type 2 to find a word and describe it\n"
                             " - Type 3 for SURPISE MODE 🎉\n"
                             " - Type 4 to quit\n" RESET;

  char *modelChoiceMessage = MAG "What model do you want to use?\n"
                                 " - Type 0 for model {Noun,Adj, Verb, Noun, Stop}\n"
                                 " - Type 1 for model {Noun, Qui, Verb, Verb, Noun, Stop}\n"
                                 " - Type 2 for model {Pronoun, Verb, Noun, Adj, Stop}\n"
                                 " - Type 3 for model {Noun,Et, Noun, Verb, Adv,Stop}\n"
                                 " - Type 10 to go BACK\n" RESET;

  while (action_choice != 4)
  {
    action_choice = getUserInput(0, 4, welcomeMessage);
    if (action_choice == 0)
    { // part for generating a random sentence
      int modelChoice = 0;
      while (modelChoice != 4) // choice of the model
      {
        int *model;
        modelChoice = getUserInput(0, 4, modelChoiceMessage);
        if (modelChoice < 4)
        {
          if (modelChoice == 0)
          {
            model = model0;
          }
          else if (modelChoice == 1)
          {
            model = model1;
          }
          else if (modelChoice == 2)
          {
            model = model2;
          }
          else if (modelChoice == 3)
          {
            model = model3;
          }
          char *fullForm = getFullFormFromModel(model, roots);
          printf(CYN "Your sentence is: %s \n" RESET, fullForm);
        }
      }
    }
    else if (action_choice == 1) // ask the user to enter his own model
    {
      int *cusModel = customModel();
      char *fullForm = getFullFormFromModel(cusModel, roots);
      printf(CYN "Your sentence is: %s \n" RESET, fullForm);
    }
    else if (action_choice == 2) // the part for describing a word
    {
      findAndDescribeWord(roots);
    }
    else if (action_choice == 3) // part for the surprise, spoiler: it's a poem
    {
      int line1Model[] = {Noun, Adj, Verb, Noun, Adj, Stop};
      int line2Model[] = {Noun, Qui, Verb, Et, Verb, Verb, Noun, Adj, Stop};
      int line3Model[] = {Noun, Adj, Verb, Adv, Noun, Stop};
      int line4Model[] = {Noun, Verb, Adv, Noun, Adj, Stop};

      printf(CYN "~ Votre Apollinaire sur mesure: \n\n" RESET);

      for (int i = 0; i < 4; i++)
      {
        char *line1 = getFullFormFromModel(line1Model, roots);
        char *line2 = getFullFormFromModel(line2Model, roots);
        char *line3 = getFullFormFromModel(line3Model, roots);
        char *line4 = getFullFormFromModel(line4Model, roots);

        printf("%s\n", line1);
        printf("%s\n", line2);
        printf("%s\n", line3);
        printf("%s\n", line4);
        printf("\n");
      }
    }
    else if (action_choice == 4)
    {
      printf(MAG "Bye bye!\n" RESET); // exit the menu
    }
  }

  return;
}

/**
 * @brief Ask the user to enter an integer between min and max (included) and return it, if the user enters a wrong value, it ask again
 *
 * @param min The minimum value the user can enter
 * @param max The maximum value the user can enter
 * @param message The message to display to the user
 * @return int The good value entered by the user
 */
int getUserInput(int min, int max, char *message)
{
  int input;
  printf("%s", message);
  scanf("%d", &input);
  while (input < min || input > max) // while the input is not between min and max we ask another input
  {
    printf(RED "Invalid input. %s" RESET, message);
    scanf("%d", &input);
  }
  return input;
}

/**
 * @brief Display the model with words instead of numbers
 *
 * @param model A list of numbers representing types of word in the model
 * @param modelSize Size of the model
 */
void displayModel(int *model, int modelSize)
{
  int i = 0;
  printf("{ ");
  while (i < modelSize)
  {
    printf("%s ", getWordTypeName(model[i]));
    i++;
  }
  printf("}");
}

/**
 * @brief Ask the user to enter a model and return it
 *
 * @return int* The list of numbers representing the model
 */
int *customModel()
{
  int *model = malloc(MAX_MODEL_LENGTH * sizeof(int));
  int input;

  int i = 0;
  while (input != 8 && i < MAX_MODEL_LENGTH - 1)
  {
    printf("Current model: "); // we print the current model
    displayModel(model, i);
    printf("\n");
    input = getUserInput(0, 8, "Enter next word type:\n- Noun (0)\n- Verb (1)\n- Adverb (2)\n- Adjective (3)\n- Pronoun (4)\n- Preposition (5)\n- Qui (6)\n- Et (7)\n- Stop (8)\n");
    if (input < 6) // put the input in the model
    {
      model[i] = input;
    }
    else if (input == 6)
    {
      model[i] = Qui;
    }
    else if (input == 7)
    {
      model[i] = Et;
    }
    else
    {
      model[i] = Stop;
    }
    i++;
  }
  if (i == MAX_MODEL_LENGTH - 1) // if the model is full we add stop at the end
  {
    model[i] = Stop;
    i++;
  }
  printf("Final model: "); // we print the model at the end
  displayModel(model, i);
  printf("\n");
  return model;
}
