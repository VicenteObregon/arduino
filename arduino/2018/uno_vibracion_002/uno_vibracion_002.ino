
bool mustBeep = false;
bool beeping = false;
int oldValue = 1023;

void setup() {
  pinMode(12, OUTPUT);
}

void loop() {
  if (mustBeep) {
    digitalWrite(12, beeping);
    delay(100);
    beeping = !beeping;
  } else {
    int aValue = analogRead(A0);

    if (aValue != oldValue) {
      mustBeep = beeping = true;
    }
  }
}

