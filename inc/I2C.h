/*
 * I2C.h
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */

#ifndef I2C_H_
#define I2C_H_

#include "fsl_i2c.h"

class I2C {
public:
	I2C(I2C_Type* I2C_Peripheral,uint32_t _deviceAddr);
	virtual ~I2C();

	status_t Write(uint32_t deviceReg,uint8_t* buffer,size_t data_length) const;
	status_t Read(uint32_t deviceReg,uint8_t* buffer,size_t data_length) const;




private:
	static i2c_master_config_t configuration;
	uint8_t deviceAddr;
	I2C_Type* Peripheral;

};

#endif /* I2C_H_ */
