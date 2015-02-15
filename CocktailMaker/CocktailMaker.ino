/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 5K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

struct Cocktail
{
  String name;
  String recipe;
};

int mRecipePosition;
Cocktail mTestCocktail;

void PrintRecipe()
{
  String recipeSubstring = mTestCocktail.recipe.substring(mRecipePosition, mRecipePosition + 16);
  
  lcd.setCursor(0, 1);
  lcd.print(recipeSubstring);
  
  if(mRecipePosition + 16 < mTestCocktail.recipe.length())
  {
    mRecipePosition++;
  }
  else
  {
    mRecipePosition = 0;
  }
  
  delay(500);
}

void setup() 
{
  mTestCocktail.name = "Screwdriver";
  mTestCocktail.recipe = "Orange Juice, Vodka";
  
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print(mTestCocktail.name);
  
  mRecipePosition = 0;
  
  PrintRecipe();
}

void loop() 
{
  PrintRecipe();
}
