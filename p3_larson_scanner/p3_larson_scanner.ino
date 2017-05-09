const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int potPin = A0;
const int n = 12;

void setup() {
  for (int i = 0; i < n; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < n; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(calculateDelay());
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = n-1; i > 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(calculateDelay());
    digitalWrite(ledPins[i], LOW);
  }
}

int calculateDelay() {
  // convert the knob postion 0..1023
  // to a delay period of 10..200 ms
  int knobPosition = analogRead(potPin);
  int t = map(knobPosition, 0, 1023, 10, 200);
  return t;
}

