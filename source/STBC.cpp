/*
 * STBC.cpp
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */

#include <STBC.h>

// const antes!
STBC::STBC(I2C* const FXASpt ,I2C* const FXOSpt) {
	uint8_t data;
	FXASpt->Read(FXAS_WHOAMI, &data, 1);
	FXASpt->Write(FXAS_WHOAMI, &data, 1);
//	this->FXAS = FXASpt;
//	this->FXOS = FXOSpt;
	// TODO Auto-generated constructor stub

}

STBC::~STBC() {
	// TODO Auto-generated destructor stub
}


void STBC::Check(){
	uint8_t data;
	FXAS->Read(FXAS_WHOAMI, &data, 1);
//	FXAS->Write(FXAS_WHOAMI, &data, 1);

}
