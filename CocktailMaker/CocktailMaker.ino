/*
  The circuit:
 * LCD RS pin to digital pin 13
 * LCD Enable pin to digital pin 12
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 2
 * LCD D6 pin to digital pin 1
 * LCD D7 pin to digital pin 0
 * LCD R/W pin to ground
 * 5K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>
#include <CocktailMenu.h>

#define SCROLL_DELAY 1000

LiquidCrystal lcd(13, 12, 4, 2, 1, 0);

bool mLastButtonState = false;
String mAvailableIngredients[] = {"Pineapple Juice", "Vodka", "Cointreau", "Cranberry Juice", "Lime Juice", "Peach Schnapps"};
CocktailMenu mCocktailMenu(mAvailableIngredients);
long mScrollCounter = 0;

void ClearScreen()
{
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
}

void PrintCocktail()
{
  long recipeScrollPosition = mScrollCounter / SCROLL_DELAY;

  if(mScrollCounter % SCROLL_DELAY == 0)
  {
    ClearScreen();

    lcd.setCursor(0, 0);
    lcd.print(mCocktailMenu.GetCurrentCocktail().name);
  
    int substringEndPos = min(recipeScrollPosition + 16, mCocktailMenu.GetCurrentCocktail().ingredients.length());
    String recipeSubstring = mCocktailMenu.GetCurrentCocktail().ingredients.substring(recipeScrollPosition, substringEndPos);

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
