#include <Wire.h>
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
 
int L3GD20_Address = 0x6B; //I2C address of the L3GD20
 
int x;
int y;
int z;
 
void setup(){
 
  Wire.begin();
  Serial.begin(9600);
 
  Serial.println("starting up L3GD20");
  setupL3GD20(2000); // Configure L3GD20  - 250, 500 or 2000 deg/sec
  pinMode(2, OUTPUT); // X +Ve value
  pinMode(3, OUTPUT); // X -Ve value
  pinMode(4, OUTPUT); // Y +Ve value
  pinMode(5, OUTPUT); // Y -Ve value
  pinMode(6, OUTPUT); // Z +Ve value
  pinMode(7, OUTPUT); // Z -Ve value
 
  delay(100); //wait for the sensor to be ready
}
 
void loop(){
   getGyroValues();  // This will update x, y, and z with new values
 
  Serial.print("X:");
  Serial.print(x);
 
  Serial.print(" Y:");
  Serial.print(y);
 
  Serial.print(" Z:");
  Serial.println(z);
 
  delay(100); //Just here to slow down the serial to make it more readable
 
  //*********LED Functions************//
 
//*********** X- position LEDs*********// 
  if (x >= 1000)
  {
   
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  }
   else if (x <= -1000)
   {
     digitalWrite(3, HIGH);
     digitalWrite(2, LOW);
   }
   else
   {
       digitalWrite(2, LOW);
       digitalWrite(3, LOW);
   }
//*********** Y- position LEDs*********// 
  if (y >= 1000)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5,LOW);
  }
  else if (y <= -1000)
  {
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
  }
   else
   {
       digitalWrite(4, LOW);
       digitalWrite(5, LOW);
   }
//*********** Z- position LEDs*********// 
  if (z >= 1000)
   {
     digitalWrite(6, HIGH);
     digitalWrite(7, LOW);
   }
   else if (z <= -1000)
   {
     digitalWrite(7, HIGH);
     digitalWrite(6, LOW);
   }
   else
   {
       digitalWrite(7, LOW);
       digitalWrite(6, LOW);
   }
//************ LED funcitons ENDs****************//
 
}
 
void getGyroValues(){
 
  byte xMSB = readRegister(L3GD20_Address, 0x29);
  byte xLSB = readRegister(L3GD20_Address, 0x28);
  x = ((xMSB << 8) | xLSB);
 
  byte yMSB = readRegister(L3GD20_Address, 0x2B);
  byte yLSB = readRegister(L3GD20_Address, 0x2A);
  y = ((yMSB << 8) | yLSB);
 
  byte zMSB = readRegister(L3GD20_Address, 0x2D);
  byte zLSB = readRegister(L3GD20_Address, 0x2C);
  z = ((zMSB << 8) | zLSB);
}
 
int setupL3GD20(int scale){
  //From  Jim Lindblom of Sparkfun's code
 
  // Enable x, y, z and turn off power down:
  writeRegister(L3GD20_Address, CTRL_REG1, 0b00001111);
 
  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3GD20_Address, CTRL_REG2, 0b00000000);
 
  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3GD20_Address, CTRL_REG3, 0b00001000);
 
  // CTRL_REG4 controls the full-scale range, among other things:
 
  if(scale == 250){
    writeRegister(L3GD20_Address, CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(L3GD20_Address, CTRL_REG4, 0b00010000);
  }else{
    writeRegister(L3GD20_Address, CTRL_REG4, 0b00110000);
  }
 
  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3GD20_Address, CTRL_REG5, 0b00000000);
}
 
void writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}
 
int readRegister(int deviceAddress, byte address){
 
    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();
 
    Wire.requestFrom(deviceAddress, 1); // read a byte
 
    while(!Wire.available()) {
        // waiting
    }
    v = Wire.read();
    return v;
}
