#include "SparkFunMPU9250-DMP.h"

MPU9250_DMP imu;

void setup() 
{
  Serial.begin(9600);

  /*
   * Setup mpu9255
   */
  
  if (imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      Serial.println("Unable to communicate with MPU-9250");
      Serial.println("Check connections, and try again.");
      Serial.println();
      delay(5000);
    }
  }
  imu.setSensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
  imu.setGyroFSR(2000);
  imu.setAccelFSR(2); 
  imu.setLPF(5);
  imu.setCompassSampleRate(10);

  /*
   * Setup analog gyro
   */

  //pinMode(AO, OUTPUT);
}

void loop() 
{
//  Serial.println("hi");
  
  if ( imu.dataReady() )
  {
  
    delay(1500);
    imu.update(UPDATE_ACCEL | UPDATE_GYRO | UPDATE_COMPASS);
    printIMUData();
  }

  double analohg = analogRead(A0);
  Serial.println();
  Serial.print(analohg);
  Serial.println();
}

void printIMUData(void)
{  
  float accelX = imu.calcAccel(imu.ax);
  float accelY = imu.calcAccel(imu.ay);
  float accelZ = imu.calcAccel(imu.az);
  float gyroX = imu.calcGyro(imu.gx);
  float gyroY = imu.calcGyro(imu.gy);
  float gyroZ = imu.calcGyro(imu.gz);
  float magX = imu.calcMag(imu.mx);
  float magY = imu.calcMag(imu.my);
  float magZ = imu.calcMag(imu.mz);
  
  Serial.println("Accel: " + String(accelX) + ", " +
              String(accelY) + ", " + String(accelZ) + " g");
  Serial.println("Gyro: " + String(gyroX) + ", " +
              String(gyroY) + ", " + String(gyroZ) + " dps");
  Serial.println("Mag: " + String(magX) + ", " +
              String(magY) + ", " + String(magZ) + " uT");
  Serial.println("Time: " + String(imu.time) + " ms");
  Serial.println();
}
