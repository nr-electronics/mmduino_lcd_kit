const int ledPins[] = {
  13,     12, 
  10,  8, 11, 
  7,       6
};

const byte throws[] = {
//   6543210  
  0b00001000, // 1 thrown
  0b01000001, // 2
  0b01001001, // 3
  0b01100011, // 4
  0b01101011, // 5
  0b01110111, // 6  
};

const int switchPin = A2;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(A0));
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    int shakes = random(10, 30);
    for (int i = 0; i < shakes; i++) {
      int x = random(6);
      show(x);
      delay(100);
    }
  }
}

void show(int x) {
  byte bitPattern = throws[x];  
  for (int i = 0; i < 7; i++) {
    digitalWrite(ledPins[i], bitRead(bitPattern, i));
  }
}
