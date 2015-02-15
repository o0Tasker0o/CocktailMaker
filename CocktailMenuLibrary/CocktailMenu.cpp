#include "Arduino.h"
#include "CocktailMenu.h"

CocktailMenu::CocktailMenu()
{
}

Cocktail CocktailMenu::GetCurrentCocktail()
{
    Cocktail currentCocktail;
    currentCocktail.name = "Screwdriver...";
    currentCocktail.recipe = "Vodka, Orange juice";
    return currentCocktail;
}