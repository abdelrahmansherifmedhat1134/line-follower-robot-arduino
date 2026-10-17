#include<LiquidCrystal.h>
//liquid crystal lcd()
LiquidCrystal lcd(12,13,6,5,4,3);
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Abdelrahman");
  lcd.setCursor(0,2);
  lcd.print("Sherif");
}

void loop()
{
  
}