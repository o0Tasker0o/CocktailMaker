#include "Arduino.h"
#include "CocktailMenu.h"

CocktailMenu::CocktailMenu()
{
    mCocktailIndex = 0;

    mCocktails[0].name = "Screwdriver";
    mCocktails[0].recipe = "Vodka, Orange Juice";

    mCocktails[1].name = "Cosmopolitan";
    mCocktails[1].recipe = "Vodka, Cointreau, Cranberry Juice, Lime Juice";
}

Cocktail CocktailMenu::GetCurrentCocktail()
{
    return mCocktails[mCocktailIndex];
}

void CocktailMenu::SelectNextCocktail()
{
    mCocktailIndex++;

    if(mCocktailIndex >= COCKTAIL_COUNT)
    {
        mCocktailIndex = 0;
    }
}