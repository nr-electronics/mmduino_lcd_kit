#include <LiquidCrystal.h>

//                RS EN D4 D5 D6 D7
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

const int setSwitchPin = 12;
const int runSwitchPin = A2;
const int buzzerPin = 11;

const int SET_MODE = 1;
const int RUN_MODE = 2;
const int ALARM_MODE = 3;

int mode = SET_MODE;
int mins = 4;
int secs = 0;
long lastUpdateTime = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("My Egg Timer");
  pinMode(setSwitchPin, INPUT_PULLUP);
  pinMode(runSwitchPin, INPUT_PULLUP);
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
  if (digitalRead(runSwitchPin) == LOW) {
    mode = RUN_MODE;
    return;
  }
  if (digitalRead(setSwitchPin) == LOW) {
    mins ++;
    if (mins > 10) {
      mins = 0;
    }
    delay(200);
  }
}

void handleRunMode() {
  if (digitalRead(runSwitchPin) == LOW) {
    mode = SET_MODE;
    delay(200);
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
  if (digitalRead(setSwitchPin) == LOW) {
    mode = SET_MODE;
    noTone(buzzerPin);
    mins = 4;
    secs = 0;
  }
}

int checkSwitch(int pin) {
  // 0 - not pressed, 1 - short press, 2 - long press
  if (digitalRead(pin) == HIGH) {
    return 0;
  }
  long t1 = millis();
  while (digitalRead(pin) == LOW) {};
  long t2 = millis();
  if ((t2 - t1) > 500) {
    return 2;
  }
  return 1;
}

