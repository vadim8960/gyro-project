#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(0x6B);
  Wire.requestFrom(0x6B, 2);
  while (Wire.available()) {
    int data[3];
    for (int i = 0; i < 4; ++i)
      data[i] = Wire.read();
    for (int i = 0; i < 4; ++i){
      Serial.print(data[i]);
      Serial.print(' ');
    }
    Serial.println();
  }
  delay(500);
}
