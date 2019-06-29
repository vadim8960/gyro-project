#include <Wire.h>
//#include "STL3GD20.h"
//#include "STLISY300AL.h"
#include "SparkFunMPU9250-DMP.h"

//L3GD20 gyro_i2c(0x6A);
//LISY300AL gyro_analog(A0);
MPU9250_DMP mpu;

void startGyro();
  
void setup() {
  Wire.begin();
  Serial.begin(9600);
  startGyro();
}

void loop() {
//  gyro_i2c.updateData();
//  Serial.print("Data from i2c gyro: ");
//  Serial.print(gyro_i2c.getX()); Serial.print(' ');
//  Serial.print(gyro_i2c.getY()); Serial.print(' ');
//  Serial.print(gyro_i2c.getZ()); Serial.println(' ');

//  Serial.print("Data from analog gyro: ");
//  Serial.println(gyro_analog.getPosition());

  mpu.updateAccel();
  Serial.print("Data from MPU9250: ");
  Serial.print(mpu.calcAccel(mpu.ax)); Serial.print(' ');
  Serial.print(mpu.calcAccel(mpu.ay)); Serial.print(' ');
  Serial.print(mpu.calcAccel(mpu.az)); Serial.println();

  delay(1000);
}

void startGyro() {
    
  // Start MPU9250 
  if (mpu.begin() != INV_SUCCESS) {
    while (1) {
      Serial.println("Unable to communicate with MPU-9250");
      Serial.println("Check connections, and try again.");
      Serial.println();
      delay(12000);
    }
  }
  mpu.dmpBegin(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_GYRO_CAL, 10);
  while (!mpu.fifoAvailable() && !mpu.dmpUpdateFifo() == INV_SUCCESS); 
  
  // Start L3GD20
  //gyro_i2c.setupL3GD20(2000);

  // Start LISY300AL
//  gyro_analog.setupLISY300AL();
}
