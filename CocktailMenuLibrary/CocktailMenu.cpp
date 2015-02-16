#include "Arduino.h"
#include "CocktailMenu.h"

CocktailMenu::CocktailMenu(String *availableIngredients)
{
    mAvailableIngredients = availableIngredients;

    mCocktails[0].name = "Screwdriver";
    mCocktails[0].ingredients = "Vodka, Orange Juice";

    mCocktails[1].name = "Cosmopolitan";
    mCocktails[1].ingredients = "Vodka, Cointreau, Cranberry Juice, Lime Juice";

    mCocktails[2].name = "Sex on the Beach";
    mCocktails[2].ingredients = "Peach Schnapps, Vodka, Pineapple Juice, Cranberry Juice";

    mCocktailIndex = -1;
    SelectNextCocktail();
}

Cocktail CocktailMenu::GetCurrentCocktail()
{
    return mCocktails[mCocktailIndex];
}

void CocktailMenu::SelectPreviousCocktail()
{
    do
    {
        mCocktailIndex--;

        if(mCocktailIndex < 0)
        {
            mCocktailIndex = COCKTAIL_COUNT - 1;
        }
    }
    while(!IngredientsAreAvailable());
}

void CocktailMenu::SelectNextCocktail()
{
    do
    {
        mCocktailIndex++;

        if(mCocktailIndex >= COCKTAIL_COUNT)
        {
            mCocktailIndex = 0;
        }
	}
    while(!IngredientsAreAvailable());
}

bool CocktailMenu::IngredientsAreAvailable()
{
    Cocktail currentCocktail = mCocktails[mCocktailIndex];
    int ingredientCount = GetIngredientCount(currentCocktail.ingredients);

    String neededIngredients[ingredientCount];

    int ingredientIndex = 0;
    int lastCommaPosition = -2;
    int nextCommaPosition = currentCocktail.ingredients.indexOf(',');

    while(nextCommaPosition != -1)
    {
        neededIngredients[ingredientIndex++] = currentCocktail.ingredients.substring(lastCommaPosition + 2, nextCommaPosition);
        lastCommaPosition = nextCommaPosition;
        nextCommaPosition = currentCocktail.ingredients.indexOf(',', nextCommaPosition + 1);
    }

    neededIngredients[ingredientIndex] = currentCocktail.ingredients.substring(lastCommaPosition + 2, nextCommaPosition);

    for(int neededIngredientIndex = 0; neededIngredientIndex < ingredientCount; ++neededIngredientIndex)
    {
        bool ingredientFound = false;

        for(int availableIngredientIndex = 0; availableIngredientIndex < 6; ++availableIngredientIndex)
        {
            if(neededIngredients[neededIngredientIndex] == mAvailableIngredients[availableIngredientIndex])
            {
                ingredientFound = true;
                break;
            }
        }

        if(!ingredientFound)
        {
            return false;
        }
    }

    return true;
}

int CocktailMenu::GetIngredientCount(String ingredientsList)
{
    int ingredientCount = 1;

    for(int characterIndex = 0; characterIndex < ingredientsList.length(); ++characterIndex)
    {
        if(ingredientsList[characterIndex] == ',')
        {
            ingredientCount++;
        }
    }

    return ingredientCount;
}