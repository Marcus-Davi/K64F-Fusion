/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    K64F-Controle.cpp
 * @brief   Application entry point.
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "Control.h"
#include "Matrix.h"
#include "IMU.h"
#include "Quaternion.h"

#include "EKF.h"
//#include "EKF_Stack.h"

#include "ModelFunctions.h"
STBC* IMUpt;


/* TODO: insert other definitions and declarations here. */
void ControlLaw();

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();


    Control::setSamplingFrequency(5);
    Control::setControlLawHandle(ControlLaw);
    Control::stop();

    I2C FXAS(I2C1,FXAS_DEVADDR);
    I2C FXOS(I2C1,FXOS_DEVADDR);


    STBC ImuShield(&FXAS,&FXOS);
    if ( ImuShield.Check() == false){
    	LED_RED_ON();
    	Control::delay(1000000);
    	LED_RED_OFF();
    }

    IMUpt = &ImuShield;

    ImuShield.Init();
    ImuShield.ClearMagOffset();


    //Covariances
    float KQ_Qn[4*4] = {
    		0.001, -0.0003, 0.0003, 0.0003,
    		-0.0003,0.0001,-0.0001,-0.0001,
    		0.0003,-0.0001,0.0001,0.0001,
    		0.0003,-0.0001,0.0001,0.0001
    }; //3x3 n x n

    float KQ_Rn[6*6] = {
    		0.1,0,0,0,0,0,
    		0,0.1,0,0,0,0,
    		0,0,0.1,0,0,0,
    		0,0,0,2,0,0,
    		0,0,0,0,2,0,
    		0,0,0,0,0,3,
    }; //3x3 out x out

    float Xq[] = {1,0,0,0};

    // Extended Kalman Filter
    Kalman::EKF ExtFilter(4,3,6);

//    Kalman::EKF_Stack ExtFilter;

//    unsigned int k = ExtFilter.GetBytesUsed();
//     CONTROLE_PRINT("bytes = %d\r\n",k);


    ExtFilter.SetQn(KQ_Qn);
    ExtFilter.SetRn(KQ_Rn);
    ExtFilter.SetX0(Xq);
    ExtFilter.SetStateFunction(AttitudeEstimation::StateFunction);
    ExtFilter.SetMeasurementFunction(AttitudeEstimation::MeasurementFunction);
    ExtFilter.SetStateJacobian(AttitudeEstimation::StateJacobian);
    ExtFilter.SetMeasurementJacobian(AttitudeEstimation::MeasurementJacobian);

    Quaternion* q = (Quaternion*)ExtFilter.GetEstimatedState(); //Perigoso ? kk

    float sys_input[3];
    float sys_measure[6];
    // Raw Data
    IMUData Accelerations_raw;
    IMUData AngularVels_raw;
    IMUData Mag_raw;

    // Converted Data
    IMUDataf Accelerations;
    IMUDataf AngularVels;
    IMUDataf Mag;




    LED_BLUE_ON();
    ImuShield.CalibrateGyroscope(50);
    //ImuShield.CalibrateAccelerometer(50); // Implementar calibração dinâmica
    LED_BLUE_OFF();




    while(1) {
    	LED_GREEN_TOGGLE();
    	ImuShield.ReadMagAcc();
    	ImuShield.ReadGyr();
    	ImuShield.AutoCalibrateMagnetometer(); // FUNDAMENTAL!!



    	ImuShield.GetGyroscopeMeasurements(AngularVels_raw);
    	ImuShield.GetAccelerometerMeasurements(Accelerations_raw);
    	ImuShield.GetMagnetometerMeasurements(Mag_raw);


    	//A "calibração" abaixo tá causando probs.. verificar
    	ImuShield.GetAccelerations(Accelerations, STBC::NON_CALIBRATED);
    	ImuShield.GetAngularVelocities(AngularVels, STBC::CALIBRATED);
    	ImuShield.GetMagnetic(Mag,STBC::CALIBRATED);

    	CONTROLE_PRINT("%f %f %f %f %f %f %f %f %f\r\n",
    			-Accelerations.Y, Accelerations.X, Accelerations.Z,
    			-AngularVels.Y, AngularVels.X, AngularVels.Z,
				-Mag.Y,Mag.X,Mag.Z);

    	mag_field = ImuShield.GetMagField();



    	sys_input[1] = (AngularVels.X ); //wx
    	sys_input[0] = -(AngularVels.Y ) ; //wy
    	sys_input[2] = (AngularVels.Z ) ; //wz
////
    	sys_measure[1] = (Accelerations.X ) ; //ax
    	sys_measure[0] = -(Accelerations.Y ); //ay
    	sys_measure[2] = (Accelerations.Z ) ; //az

    	sys_measure[4] = (Mag.X ) ; //ax
    	sys_measure[3] = -(Mag.Y ) ; //ay
    	sys_measure[5] = (Mag.Z ); //az


    	ExtFilter.Predict(sys_input);
    	ExtFilter.Update(sys_measure);


//    	CONTROLE_PRINT("%f %f %f %f\r\n",q->w,q->v.x,q->v.y,q->v.z);
//    	CONTROLE_PRINT("%f %f %f\r\n",AngularVels.X,AngularVels.Y,AngularVels.Z);



    }


    return 0;
}


//lei de Controle;
void ControlLaw(){
//LED_BLUE_TOGGLE();

}

