#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
    pinMode(32, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(32, HIGH);
  delay(500);
  digitalWrite(32, LOW);
  delay(500);
}