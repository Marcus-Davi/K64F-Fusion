/*
 * STBC.h
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */

#ifndef STBC_H_
#define STBC_H_

#include <cmath>
#include <arm_math.h> // for PI

/*STBC Device Registers*/
#define FXOS_DEVADDR 0x1E
#define FXAS_DEVADDR 0x20

#define FXOS_WHOAMI 0x0D
#define FXOS_WHOAMI_ID 0xC7
#define FXOS_STATUS_REG 0x00
#define FXOS_CTROL_REG1 0x2A
#define FXOS_CTROL_REG2 0x2B
#define FXOS_CTROL_REG3 0x2C
#define FXOS_M_CTROL_REG1 0x5B
#define FXOS_M_CTROL_REG2 0x5C
#define FXOS_M_CTROL_REG3 0x5D
#define FXOS_XYZ_DATA_CFG 0x0E
#define FXOS_OUT_X_MSB 0x01
#define FXOS_M_OUT_X_MSB 0x33 /*16 bits(2 registradores) por eixo. 2's Complement*/
#define FXOS_OFF_X 0x2F
#define FXOS_OFF_Y 0x30
#define FXOS_OFF_Z 0x31
#define FXOS_MAX_X_MSB 0x45

#define FXAS_DR_STATUS 0x07
#define FXAS_WHOAMI 0x0C
#define FXAS_WHOAMI_ID 0xD7
#define FXAS_OUT_X_MSB 0x01
#define FXAS_CTRL_REG0 0x0D
#define FXAS_CTRL_REG1 0x13
#define FXAS_CTRL_REG2 0x14
#define FXAS_CTRL_REG3 0x15

// bit to metric conversion
// Meanwhile, using #defines .. need to implement dynamic later
#define ACC_CONVERSION 0.488e-3 * 9.80665
#define GYR_CONVERSION 15.625e-3 * PI/180.0
#define MAG_CONVERSION 0.1

// ACC CALIBRATIONS
/*

W =

    1.0062         0         0
         0    1.0047         0
         0         0    1.0152


V =

   -0.0223
    0.0150
   -0.0414

 */

#include "I2C.h" // For IMU Pointers

//Data Storage
struct IMUData {
	int16_t X;
	int16_t Y;
	int16_t Z;
};

struct IMUDataf {
	float X;
	float Y;
	float Z;
};

//This class handles communication with the sensor shield.

class STBC {
public:

	enum Mode {
		CALIBRATED,
		NON_CALIBRATED
	};

	STBC(const I2C *FXASpt, const I2C *FXOSpt); //Tem Forma melhor ?
	virtual ~STBC();

	bool Check();
	void Init();
	void ReadMagAcc();
	void ReadGyr();

	void CalibrateGyroscope(int Samples);
	void CalibrateAccelerometer(int Samples);
	void AutoCalibrateMagnetometer();
	void ClearMagOffset();
	float GetMagField();

	// CONVERTED DATA

	inline void GetAccelerations(IMUDataf &A, Mode m = CALIBRATED) {
		if (m == STBC::NON_CALIBRATED){
		A.X = Accelerometer.X * ACC_CONVERSION;
		A.Y = Accelerometer.Y * ACC_CONVERSION;
		A.Z = Accelerometer.Z * ACC_CONVERSION;
		} else {
			A.X = (Accelerometer.X * ACC_CONVERSION * 1.0033) - 0.1896;
			A.Y = (Accelerometer.Y * ACC_CONVERSION * 0.9911) + 0.1921;
			A.Z = (Accelerometer.Z * ACC_CONVERSION * 1.0190) - 0.4438;

		}

	}
	inline void GetAngularVelocities(IMUDataf &G, Mode m = CALIBRATED) {

		if(m == NON_CALIBRATED) {
		G.X = Gyroscope.X * GYR_CONVERSION;
		G.Y = Gyroscope.Y * GYR_CONVERSION;
		G.Z = Gyroscope.Z * GYR_CONVERSION;
		} else {
			G.X = (Gyroscope.X - Gyroscope_Offset.X) * GYR_CONVERSION;
			G.Y = (Gyroscope.Y - Gyroscope_Offset.Y) * GYR_CONVERSION;
			G.Z = (Gyroscope.Z - Gyroscope_Offset.Z) * GYR_CONVERSION;
		}
	}


	inline void GetMagnetic(IMUDataf &M, Mode m = CALIBRATED) {
		if( m == NON_CALIBRATED) {
		M.X = Magnetometer.X * MAG_CONVERSION;
		M.Y = Magnetometer.Y * MAG_CONVERSION;
		M.Z = Magnetometer.Z * MAG_CONVERSION;
		} else {
			M.X = (Magnetometer.X - Magnetometer_Offset.X) * MAG_CONVERSION;
			M.Y = (Magnetometer.Y - Magnetometer_Offset.Y) * MAG_CONVERSION;
			M.Z = (Magnetometer.Z - Magnetometer_Offset.Z) * MAG_CONVERSION;
		}
	}



	// RAW DATA

	inline void GetAccelerometerMeasurements(IMUData &A) const {
		A.X = Accelerometer.X;
		A.Y = Accelerometer.Y;
		A.Z = Accelerometer.Z;
	}
	inline void GetGyroscopeMeasurements(IMUData &G) const {
		G.X = Gyroscope.X;
		G.Y = Gyroscope.Y;
		G.Z = Gyroscope.Z;
	}
	inline void GetMagnetometerMeasurements(IMUData &M) const {
		M.X = Magnetometer.X;
		M.Y = Magnetometer.Y;
		M.Z = Magnetometer.Z;
	}

	// TODO Calibration Functions

private:
	const I2C *FXAS = nullptr;
	const I2C *FXOS = nullptr;
	IMUData Accelerometer;
	IMUData Gyroscope;
	IMUData Magnetometer;

	IMUData Accelerometer_Offset = {0};
	IMUData Gyroscope_Offset = {0};
	IMUData Magnetometer_Offset = {0};

//	IMUDataf Accelerations;
	//IMUDataf Accelerations;
	//IMUDataf Accelerations;

//	IMUDataf Accelerometer_Gain = { 0, 0, 0 };
	//IMUDataf Gyroscope_Gain;
	//IMUDataf Magnetometer_Gain;

};

#endif /* STBC_H_ */
