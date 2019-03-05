#include "STL3GD20.h"
#include "STLISY300AL.h"

L3GD20 gyro(0x6A);
LISY300AL gyro_analog(A0);

void setup() {
  Serial.begin(9600);
  gyro.setupL3GD20(2000);
//  gyro.setupLISY300AL();
}

void loop() {
  gyro.updateData();
  Serial.print(gyro.getX()); Serial.print(' ');
  Serial.print(gyro.getY()); Serial.print(' ');
  Serial.print(gyro.getZ()); Serial.println(' ');
  delay(100);

//  Serial.println(gyro.getPosition());
//  delay(100);
}
