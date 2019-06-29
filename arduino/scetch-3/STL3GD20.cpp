#include "STL3GD20.h"

void L3GD20::writeRegister(int deviceAddress, unsigned char address, unsigned char val) {
	Wire.beginTransmission(deviceAddress);
    Wire.write(address);
    Wire.write(val);
    Wire.endTransmission();
}

int L3GD20::readRegister(int deviceAddress, unsigned char address){
    int value;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(deviceAddress, 1);
    while(!Wire.available());
    value = Wire.read();
    return value;
}

L3GD20::L3GD20(/*unsigned Address = 0x6B*/) {
	Wire.begin();
	//L3GD20_Address = Address;
	x = y = z = 0;
}

void L3GD20::setupL3GD20(unsigned scale){
	writeRegister(L3GD20_Address, CTRL_REG1, 0b00001111);
 
	writeRegister(L3GD20_Address, CTRL_REG2, 0b00000000);
 
	writeRegister(L3GD20_Address, CTRL_REG3, 0b00001000);
 
	if(scale == 250)
		writeRegister(L3GD20_Address, CTRL_REG4, 0b00000000);
	else if(scale == 500)
		writeRegister(L3GD20_Address, CTRL_REG4, 0b00010000);
	else
		writeRegister(L3GD20_Address, CTRL_REG4, 0b00110000);
 
	writeRegister(L3GD20_Address, CTRL_REG5, 0b00000000);
}

void L3GD20::updateData() {
	unsigned char xLSB = readRegister(L3GD20_Address, LOW_BYTE_X);
	unsigned char xMSB = readRegister(L3GD20_Address, HIGH_BYTE_X);
	x = ((xMSB << 8) | xLSB);
	 
	unsigned char yLSB = readRegister(L3GD20_Address, LOW_BYTE_Y);
	unsigned char yMSB = readRegister(L3GD20_Address, HIGH_BYTE_Y);
	y = ((yMSB << 8) | yLSB);
	 
	unsigned char zLSB = readRegister(L3GD20_Address, LOW_BYTE_Z);
	unsigned char zMSB = readRegister(L3GD20_Address, HIGH_BYTE_Z);
	z = ((zMSB << 8) | zLSB);
}

int L3GD20::getX() { return x; }

int L3GD20::getY() { return y; }

int L3GD20::getZ() { return z; }
