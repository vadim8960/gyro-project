#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(0x6B);
  Wire.requestFrom(0x6B, 2);
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print((int)c);
    Serial.println(' ');
  }
  delay(500);
}
