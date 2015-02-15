#ifndef COCKTAILMENU_H
#define COCKTAILMENU_H

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
};

#endif