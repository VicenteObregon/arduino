
int oldValue = 0;
unsigned long nextEvent = 0;
unsigned long waitTime = 1000;
bool beep = false;
int maxValue = 600;

void setup() {
  pinMode(12, OUTPUT);
}

void loop() {
  int aValue = analogRead(A0);

  if (aValue != oldValue) {
    if (aValue > maxValue) {
      aValue = maxValue;
    }
    oldValue = aValue;
    aValue = map(aValue, 0, maxValue, 0, 10);
    waitTime = 100 * ((10 - aValue) + 1);
  }
  if (aValue > 0) {
    if (millis() > nextEvent) {
      beep = !beep;
      digitalWrite(12, beep);
      nextEvent = millis() + waitTime;
    }
  } else {
    digitalWrite(12, false);
  }
}
