/*
 * Interrupts.cpp
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */


#include "inc/Interrupt.h"

#if defined (__cplusplus)
extern "C" {
#endif

/* PIT0_IRQn interrupt handler */
void PIT_CHANNEL_0_IRQHANDLER(void) {
  PIT_ClearStatusFlags(PIT_PERIPHERAL, kPIT_Chnl_0, kPIT_TimerFlag);
  LED_BLUE_TOGGLE();
}





#if defined (__cplusplus)
} // extern "C"
#endif
