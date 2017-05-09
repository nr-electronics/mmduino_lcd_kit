#include <LiquidCrystal.h>

//                RS EN D4 D5 D6 D7
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

const int tempPin = A3;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Temperature");
}

void loop() {
  lcd.setCursor(0, 1);
  float tempC = readTemp();
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  lcd.print(tempC);
  lcd.print(" C  ");
  lcd.print(tempF);
  lcd.print(" F");  
  delay(500);
}

float readTemp() {
  int raw = analogRead(tempPin);
  float volts = raw / 205.0;
  float tempC = 100.0 * volts - 50;
  return tempC;
}
