/*
 * STBC.cpp
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */

#include <STBC.h>

// const antes!
STBC::STBC(const I2C* FXASpt ,const I2C* FXOSpt) {
	FXAS = FXASpt;
	FXOS = FXOSpt;

}

STBC::~STBC() {
	// TODO Auto-generated destructor stub
}


bool STBC::Check(){
	uint8_t data;
	FXAS->Read(FXAS_WHOAMI, &data, 1);
	if (data != FXAS_WHOAMI_ID)
		return false;
	FXOS->Read(FXOS_WHOAMI, &data, 1);
	if (data != FXOS_WHOAMI_ID)
		return false;
	return true;
//	FXAS->Write(FXAS_WHOAMI, &data, 1);

}

void STBC::Init(){
	//Configuracao do FXOS(Acc + MAG)
	uint8_t tx;

	tx = 0x00;//Modo Standby.

	FXOS->Write(FXOS_CTROL_REG1, &tx, 1);

	tx=0x03;//Ligar modo Hybrid, 2x Oversampling.
	FXOS->Write(FXOS_M_CTROL_REG1, &tx, 1);

	tx=0x22;//Hybrid AutoIncrement + Magnetic Reset.
	FXOS->Write(FXOS_M_CTROL_REG2, &tx, 1);

	tx=0x01;//0.488mg/LSB + NO HighPassFilter. | 4g
	FXOS->Write(FXOS_XYZ_DATA_CFG, &tx, 1);

	tx=0b00011101;//Modo Ativo,Read Normal,Low Noise, 50 Hz.
	FXOS->Write(FXOS_CTROL_REG1, &tx, 1);

	//Configuracao do FXAS(Gyro)

	tx = 0b00000000; //Standby
	FXAS->Write(FXAS_CTRL_REG1, &tx, 1);

	// {  BW[7:6] SPIW SEL[4:3] HPF_EN FS[1:0]  }
	tx = 0b00000010; //LP 16Hz, +-500dps, 15.625 mdps/LSB
	FXAS->Write(FXAS_CTRL_REG0, &tx, 1);;

	// [- RST ST DR[4:2] ACTIVE READY]
	tx = 0b00010010; //ORD = 50 Hz, Active
	FXAS->Write(FXAS_CTRL_REG1, &tx, 1);

}

void STBC::ReadMagAcc(){
//	FXOSWaitDataReady();

	uint8_t Dataready = 0;
	while (Dataready != 0x07) { //os 3 dados prontos
		FXOS->Read(FXOS_STATUS_REG, &Dataready, 1);
		Dataready &= 0x07; //AND MASK
	}

	uint8_t buffer[12] = { 0 };
	FXOS->Read(FXOS_OUT_X_MSB, buffer, 12);

	Accelerometer.X = (int16_t) ((buffer[0] << 8) | buffer[1]) >> 2;
	Accelerometer.Y = (int16_t) ((buffer[2] << 8) | buffer[3]) >> 2;
	Accelerometer.Z = (int16_t) ((buffer[4] << 8) | buffer[5]) >> 2;

	Magnetometer.X = (int16_t) (buffer[6] << 8) | buffer[7];
	Magnetometer.Y = (int16_t) (buffer[8] << 8) | buffer[9];
	Magnetometer.Z = (int16_t) (buffer[10] << 8) | buffer[11];
}

void STBC::ReadGyr(){
//	FXASWaitDataReady();

	uint8_t Dataready = 0;
	while (Dataready != 0x0f) {
		FXAS->Read(FXAS_DR_STATUS, &Dataready, 1);
		Dataready &= 0x0f; //AND MASK
	}

	uint8_t buffer[6] = { 0 };
	FXAS->Read(FXAS_OUT_X_MSB, buffer, 6);
	Gyroscope.X = (int16_t) ((buffer[0] << 8) | buffer[1]);
	Gyroscope.Y = (int16_t) ((buffer[2] << 8) | buffer[3]);
	Gyroscope.Z = (int16_t) ((buffer[4] << 8) | buffer[5]);
}


void STBC::CalibrateGyroscope(int Samples){
	long int Mx = 0, My = 0, Mz = 0;
	for (int i = 0; i < Samples; ++i) {
		ReadGyr();
		Mx += Gyroscope.X;
		My += Gyroscope.Y;
		Mz += Gyroscope.Z;
	}
	Gyroscope_Offset.X = Mx/Samples;
	Gyroscope_Offset.Y = My/Samples;
	Gyroscope_Offset.Z = Mz/Samples;
}

// Os valores abaixo foram medidos alinhado o módulo com gravidade
// MAX_Z = 2102 | MIN_Z = -1935
// MAX_X = 2082 | MIN_X = 1991
// MAX_Y = 2009 | MIN_Y = 2070



void STBC::CalibrateAccelerometer(int Samples){
	long int MAx=0,MAy=0,MAz = 0;
	for(int i=0;i<Samples;++i){
	ReadMagAcc();
	MAx += Accelerometer.X;
	MAy += Accelerometer.Y;
	MAz += Accelerometer.Z;
	}


	Accelerometer_Offset.X = MAx/Samples; //Media de medidas Ax
	Accelerometer_Offset.Y = MAy/Samples; //Media de medidas Ay
	Accelerometer_Offset.Z = MAz/Samples - 2049;//Correto = 2049 (gravidade)
}

void STBC::AutoCalibrateMagnetometer(){
	uint8_t buffer[12];
	int16_t Xmax,Xmin,Ymax,Ymin,Zmax,Zmin;
	FXOS->Read(FXOS_MAX_X_MSB, buffer, 12);
			Xmax = buffer[0]<<8 | buffer[1];
			Ymax = buffer[2]<<8 | buffer[3];
			Zmax = buffer[4]<<8 | buffer[5];
			Xmin = buffer[6]<<8 | buffer[7];
			Ymin = buffer[8]<<8 | buffer[9];
			Zmin = buffer[10]<<8 | buffer[11];

			Magnetometer_Offset.X = (Xmax+Xmin)/2;
			Magnetometer_Offset.Y = (Ymax+Ymin)/2;
			Magnetometer_Offset.Z = (Zmax+Zmin)/2;
}

void STBC::ClearMagOffset(){
	uint8_t rx;
	FXOS->Read(FXOS_M_CTROL_REG2, &rx, 1);
	rx |= (1<<2);
	FXOS->Write(FXOS_M_CTROL_REG2, &rx, 1);
}

float STBC::GetMagField(){
	float Bx = (Magnetometer.X - Magnetometer_Offset.X)*0.1;
	float By = (Magnetometer.Y - Magnetometer_Offset.Y)*0.1;
	float Bz = (Magnetometer.Z - Magnetometer_Offset.Z)*0.1;

	return sqrtf(Bx*Bx + By*By + Bz*Bz);
}




