
int oldValue = -1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A0);

  if (value != oldValue) {
    Serial.println(value);
    oldValue = value;
  }
}

