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

#define SCROLL_DELAY 1000

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool mLastButtonState = false;
String mAvailableIngredients[] = {"Pineapple Juice", "Vodka", "Cointreau", "Cranberry Juice", "Lime Juice", "Peach Schnapps"};
CocktailMenu mCocktailMenu(mAvailableIngredients);
int mScrollCounter = 0;

void PrintCocktail()
{
  int recipeScrollPosition = mScrollCounter / SCROLL_DELAY;

  if(mScrollCounter % SCROLL_DELAY == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print(mCocktailMenu.GetCurrentCocktail().name);
  
    String recipeSubstring = mCocktailMenu.GetCurrentCocktail().ingredients.substring(recipeScrollPosition, recipeScrollPosition + 16);

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(recipeSubstring);
  }
  
  if(recipeScrollPosition + 12 < mCocktailMenu.GetCurrentCocktail().ingredients.length())
  {
    mScrollCounter++;
  }
  else
  {
    mScrollCounter = 0;
  }
}

void setup() 
{
  pinMode(A5, INPUT_PULLUP);
  
  lcd.begin(16, 2);
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
      mScrollCounter = 0;
    }

    mLastButtonState = true;
  }
  else
  {
    mLastButtonState = false;
  }

  PrintCocktail();
}
