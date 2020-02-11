/*
 * Control.h
 *
 *  Created on: 13 de set de 2019
 *      Author: marcus
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "fsl_debug_console.h"
#include "fsl_pit.h"




// Implementar :
// Setar Amostragem
// Setar ADC
// Setar DAC
// Setar PWM
// Falar com Matlab
// HIL ?


#define CONTROLE_PRINT PRINTF


typedef void (*FunPt)();

class Control {
public:

	class ADC;
	class DAC;
	class PWM;


	static void setSamplingFrequency(float Hz);
	static void setSamplingTime(float Ts);
	static void start();
	static void stop();
	static void runControl();
	static bool getControlStatus();
	static void setControlLawHandle(FunPt callback);

	//Blocking!
	static void delay(uint32_t usec);



private:
	Control();
	virtual ~Control();
	static bool isRunning;
	static FunPt ControlHandle;


};


#endif /* CONTROL_H_ */
