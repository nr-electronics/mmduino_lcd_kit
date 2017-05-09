#include <LiquidCrystal.h>

//                RS EN D4 D5 D6 D7
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

const int switchPin = A2;
const int buzzerPin = 11;

const int SET_MODE = 1;
const int RUN_MODE = 2;
const int ALARM_MODE = 3;

const int SHORT_PRESS = 1;
const int LONG_PRESS = 2;

int mode = SET_MODE;
int mins = 4;
int secs = 0;
long lastUpdateTime = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("My Egg Timer");
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  displayTime();
  if (mode == SET_MODE) {
    handleSetMode();
  }
  else if (mode == RUN_MODE) {
    handleRunMode();
  }
  else if (mode == ALARM_MODE) {
    handleAlarmMode();
  }
}

void displayTime() {
  lcd.setCursor(0, 1);
  lcd.print("     ");
  lcd.setCursor(0, 1);
  lcd.print(mins);
  lcd.print(":");
  if (secs < 10) {
    lcd.print("0");
  }
  lcd.print(secs);  
  delay(200);
}

void handleSetMode() {
  int switchPress = checkSwitch(switchPin);
  if (switchPress == LONG_PRESS) {
    mode = RUN_MODE;
    return;
  }
  if (switchPress == SHORT_PRESS) {
    mins ++;
    if (mins > 10) {
      mins = 0;
    }
  }
}

void handleRunMode() {
  if (checkSwitch(switchPin) == SHORT_PRESS) {
    mode = SET_MODE;
    return;
  }
  if (mins == 0 && secs == 0) {
    mode = ALARM_MODE;
    tone(buzzerPin, 1000);
    return;
  }
  updateTime();
}

void updateTime() {
  long now = millis();
  if (now > lastUpdateTime + 1000) {
    secs --;
    if (secs < 0) {
      secs = 59;
      mins --; 
    }
    lastUpdateTime = now;
  }
}

void handleAlarmMode() {
  if (checkSwitch(switchPin) == SHORT_PRESS) {
    mode = SET_MODE;
    noTone(buzzerPin);
    mins = 4;
    secs = 0;
  }
}

int checkSwitch(int pin) {
  static int previousState = 0;
  if (digitalRead(pin) == HIGH) {
    previousState = 0;
    return 0;
  }
  else if (previousState == 0) // and button down
  {
    long t0 = millis();
    while (digitalRead(pin) == LOW) {
      if ((millis() - t0) > 1000) {
        previousState = LONG_PRESS;
        return LONG_PRESS;
      }
    }
    previousState = SHORT_PRESS;
    return SHORT_PRESS;
  }
  return 0;
}

