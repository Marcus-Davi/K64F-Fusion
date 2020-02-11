/*
 * I2C.cpp
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */

#include <I2C.h>


// Classe para comunicação com dispositivos I2C
// As pinagens precisam estar setadas na configuração de pinos
// SUGESTÃO: Criar um Arquivo .h com #defines dos endereços e parâmetros. Ex: IMU.h

//Construtor (Periféricos do I2C, endereço do dispositivo I2C)
I2C::I2C(I2C_Type* I2C_Peripheral,uint32_t _deviceAddr) {
	// TODO Auto-generated constructor stub
	//Verificar se já foi inicializado
	Peripheral = I2C_Peripheral;
	I2C_MasterInit(Peripheral, &configuration, CLOCK_GetBusClkFreq());
	deviceAddr = _deviceAddr;

}


//Deconstrutor
I2C::~I2C() {
	// TODO Auto-generated destructor stub
	I2C_MasterDeinit(Peripheral);
}

//Escrita (subendereço/registrador do dispositivo, dados, tamanho dos dados)
status_t I2C::Write(uint32_t deviceReg,uint8_t* buffer,size_t data_length){
	i2c_master_transfer_t xfer;
	xfer.data = buffer;
	xfer.dataSize = data_length;
	xfer.slaveAddress = deviceAddr;
	xfer.subaddress = deviceReg;
	xfer.flags = kI2C_TransferDefaultFlag;
	xfer.subaddressSize = 1;
	xfer.direction = kI2C_Write;
	Peripheral = I2C1; // test
	return(I2C_MasterTransferBlocking(Peripheral, &xfer));

}

//Leitura (subendereço/registrador do dispositivo, dados, tamanho dos dados)
status_t I2C::Read(uint32_t deviceReg,uint8_t* buffer,size_t data_length) const {
	i2c_master_transfer_t xfer;
	xfer.data = buffer;
	xfer.dataSize = data_length;
	xfer.slaveAddress = deviceAddr;
	xfer.subaddress = deviceReg;
	xfer.flags = kI2C_TransferDefaultFlag;
	xfer.subaddressSize = 1;
	xfer.direction = kI2C_Read;

	return(I2C_MasterTransferBlocking(Peripheral, &xfer));

}


//Default Config
i2c_master_config_t I2C::configuration= {  .enableMaster = true,
		  .enableStopHold = false,
		  .baudRate_Bps = 375000,
		  .glitchFilterWidth = 0};
