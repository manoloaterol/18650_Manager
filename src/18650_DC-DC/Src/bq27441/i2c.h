#include "stm32g0xx.h"

// #define I2C_BUFFER_LEN 8

extern I2C_HandleTypeDef hi2c1;

int8_t i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
uint16_t i2cReadRegister(uint16_t addr,uint8_t regOffset);
uint16_t i2cReadRegisterBigEndian(uint16_t addr,uint8_t regOffset);
void i2cWriteRegister(uint16_t addr,uint8_t regOffset, uint8_t writeData);




uint16_t i2cReadRegister(uint16_t addr,uint8_t regOffset)
{
	uint16_t result = 0x00;

	uint8_t dataArray[2] = {0};

	i2c_read(addr, regOffset, dataArray, 2);

	result = (dataArray[1] << 8) | (dataArray[0]);
	return result;
	// return dataArray[0];
}

uint16_t i2cReadRegisterBigEndian(uint16_t addr,uint8_t regOffset)
{
	uint16_t result = 0x00;

	uint8_t dataArray[2] = {0};

	i2c_read(addr, regOffset, dataArray, 2);

	result = (dataArray[0] << 8 | dataArray[1]);
	return result;
	// return dataArray[0];
}


void i2cWriteRegister(uint16_t addr,uint8_t regOffset, uint8_t writeData)
{
	uint8_t cmdArray[1];
	uint8_t dataArray[2];

	cmdArray[0] = regOffset;
	dataArray[0] = writeData;
	i2c_write(addr, regOffset, dataArray, 2);
}



int8_t i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	return HAL_I2C_Mem_Read(&hi2c1, dev_addr<<1, reg_addr, 1, data, len, 10);

}

int8_t i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
	int8_t res;
	res =  HAL_I2C_Mem_Write(&hi2c1, dev_addr<<1, reg_addr, 1, data, len, 10);
	HAL_Delay(40);
	return res;

}
