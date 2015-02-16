#ifndef COCKTAILMENU_H
#define COCKTAILMENU_H

#define COCKTAIL_COUNT 3

#include "Arduino.h"

struct Cocktail
{
  String name;
  String ingredients;
};

class CocktailMenu
{
  public:
    CocktailMenu(String *availableIngredients);
    Cocktail GetCurrentCocktail();
    void SelectNextCocktail();
    bool IngredientsAreAvailable();
  private:
    Cocktail mCocktails[COCKTAIL_COUNT];
    int mCocktailIndex;
    String *mAvailableIngredients;

    int GetIngredientCount(String ingredientsList);
};

#endif