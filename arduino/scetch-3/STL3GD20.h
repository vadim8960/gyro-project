#ifndef _STL3GD20_H_
#define _STL3GD20_H_

#include <Wire.h>

#define CTRL_REG1    0x20
#define CTRL_REG2    0x21
#define CTRL_REG3    0x22
#define CTRL_REG4    0x23
#define CTRL_REG5    0x24
#define	LOW_BYTE_X   0x28
#define	LOW_BYTE_Y   0x2A
#define	LOW_BYTE_Z   0x2C
#define	HIGH_BYTE_X  0x29
#define	HIGH_BYTE_Y  0x2B
#define	HIGH_BYTE_Z  0x2D

class L3GD20 {
	int x;
	int y;
	int z;
	unsigned L3GD20_Address;
	void writeRegister(int deviceAddress, unsigned char address, unsigned char val);
	int readRegister(int deviceAddress, unsigned char address);
public:
	L3GD20(unsigned Address = 0x6B);
	void setupL3GD20(unsigned scale);
	void updateData();
	int getX();
	int getY();
	int getZ();
};

#endif /*_STL3GD20_H_*/