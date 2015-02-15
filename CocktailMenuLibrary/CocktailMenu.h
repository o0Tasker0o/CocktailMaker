#ifndef COCKTAILMENU_H
#define COCKTAILMENU_H

#define COCKTAIL_COUNT 2

#include "Arduino.h"

struct Cocktail
{
  String name;
  String recipe;
};

class CocktailMenu
{
  public:
    CocktailMenu();
    Cocktail GetCurrentCocktail();
    void SelectNextCocktail();
  private:
    Cocktail mCocktails[2];
    int mCocktailIndex;
};

#endif