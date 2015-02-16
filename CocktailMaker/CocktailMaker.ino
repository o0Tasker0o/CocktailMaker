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
#include <CocktailMenu.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int mRecipePosition;
bool mLastButtonState = false;
String mAvailableIngredients[] = {"Orange Juice", "Vodka", "Cointreau", "Cranberry Juice", "Lime Juice", ""};
CocktailMenu mCocktailMenu(mAvailableIngredients);

void PrintCocktail()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(mCocktailMenu.GetCurrentCocktail().name);

  String recipeSubstring = mCocktailMenu.GetCurrentCocktail().ingredients.substring(mRecipePosition, mRecipePosition + 16);
  
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(recipeSubstring);
  
  if(mRecipePosition + 12 < mCocktailMenu.GetCurrentCocktail().ingredients.length())
  {
    mRecipePosition++;
  }
  else
  {
    mRecipePosition = 0;
  }
  
  delay(400);
}

void setup() 
{
  pinMode(A5, INPUT_PULLUP);
  
  lcd.begin(16, 2);

  mRecipePosition = 0;
  
  PrintCocktail();
}

bool IsButtonPressed()
{
  int analogValue = analogRead(5);

  return analogValue < 1000;
}

void loop() 
{
  if(IsButtonPressed())
  {
    if(!mLastButtonState)
    {
      mCocktailMenu.SelectNextCocktail();
      mRecipePosition = 0;
    }

    mLastButtonState = true;
  }
  else
  {
    mLastButtonState = false;
  }

  PrintCocktail();
}
