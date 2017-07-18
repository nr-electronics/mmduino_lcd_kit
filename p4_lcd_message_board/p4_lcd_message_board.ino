#include <LiquidCrystal.h>

const int contrastPin = 2;
int contrast = 0;

//                RS EN D4 D5 D6 D7
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

void setup() {
  Serial.begin(9600);
  lcd.begin(2, 16);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MonkMakes");
  lcd.setCursor(0,1);
  lcd.print("LCD Kit");
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == '#') {
      lcd.clear();
    }
    else if (ch == '/') {
      lcd.setCursor(0,1);
    }
    else {
      lcd.write(ch);
    }
    contrast += 5;
    Serial.println(contrast);
    analogWrite(contrastPin, contrast);
  }
}
