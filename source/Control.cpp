/*
 * Control.cpp
 *
 *  Created on: 13 de set de 2019
 *      Author: marcus
 */

#include "Control.h"


void Control::setSamplingFrequency(float Hz){
	uint32_t usec = 1000000.0/Hz;
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(usec,CLOCK_GetBusClkFreq()));
}

void Control::setSamplingTime(float Ts){
	uint32_t usec = 1000000.0*Ts;
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(usec,CLOCK_GetBusClkFreq()));
}

void Control::start(){
	PIT_StartTimer(PIT, kPIT_Chnl_0);
	isRunning = true;
}

void Control::stop(){
	PIT_StopTimer(PIT, kPIT_Chnl_0);
	isRunning = false;
}

bool Control::getControlStatus(){
	return isRunning;
}


void Control::setControlLawHandle(FunPt callback){
	ControlHandle = callback;
}

void Control::runControl(){
	if(ControlHandle)
	ControlHandle();
}

//Tempo para esperar em usec
void Control::delay(uint32_t usec){
	PIT_SetTimerPeriod(PIT,kPIT_Chnl_1 , USEC_TO_COUNT(usec,CLOCK_GetBusClkFreq()));
	PIT_StartTimer(PIT, kPIT_Chnl_1);
	while(PIT_GetStatusFlags(PIT, kPIT_Chnl_1) != kPIT_TimerFlag);
	PIT_StopTimer(PIT, kPIT_Chnl_1);
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_1 , kPIT_TimerFlag);
}


Control::Control() {
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}





FunPt Control::ControlHandle = nullptr;
bool Control::isRunning = false;

