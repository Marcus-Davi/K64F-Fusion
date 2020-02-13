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
/* TODO: insert other definitions and declarations here. */
void ControlLaw();

void inline Quaternion::Print(const Quaternion& q){
CONTROLE_PRINT("%f %f %f %f\r\n",q.w,q.v.x,q.v.y,q.v.z);
}

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
    Control::start();

    I2C FXAS(I2C1,FXAS_DEVADDR);
    I2C FXOS(I2C1,FXOS_DEVADDR);


    STBC ImuShield(&FXAS,&FXOS);
    if ( ImuShield.Check() == false){
    	LED_RED_ON();
    	Control::delay(1000000);
    	LED_RED_OFF();
    }

    Quaternion a(1,2,3,4);
    Quaternion b(4,3,2,1);
    Quaternion c = a*b;

    Quaternion::Print(c);

    ImuShield.Init();

//    IMUData Data;



    while(1) {
    	LED_GREEN_TOGGLE();
    	ImuShield.ReadMagAcc();
    	ImuShield.ReadGyr();
//    	Data = ImuShield.GetAccelerometerMeasurements();
//    	CONTROLE_PRINT("A: %d %d %d",Data.X,Data.Y,Data.Z);
//    	Data = ImuShield.GetMagnetometerMeasurements();
//    	CONTROLE_PRINT("M: %d %d %d",Data.X,Data.Y,Data.Z);
//    	Data = ImuShield.GetGyroscopeMeasurements();
//    	CONTROLE_PRINT("G: %d %d %d\r\n\n",Data.X,Data.Y,Data.Z);

    }


    return 0;
}


//lei de Controle;
void ControlLaw(){
LED_BLUE_TOGGLE();

}

