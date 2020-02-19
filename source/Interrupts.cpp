/*
 * Interrupts.cpp
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */


#include "Interrupt.h"

#if defined (__cplusplus)
extern "C" {
#endif

/* PIT0_IRQn interrupt handler */
void PIT_CHANNEL_0_IRQHANDLER(void) {
	if(PIT_GetStatusFlags(PIT_PERIPHERAL, kPIT_Chnl_0)){
	PIT_ClearStatusFlags(PIT_PERIPHERAL, kPIT_Chnl_0, kPIT_TimerFlag);
	Control::runControl();
	}
}

// SW2
// OK = 0x84 = 	   10000100
// NOT OK = 0xa0 = 10100000
// NOT OK = 0x21 = 00100001
void GPIOC_IRQHANDLER(){
	GPIO_PortClearInterruptFlags(GPIOC, 1 << BOARD_SW2_GPIO_PIN);
	uint8_t stats = I2C_MasterGetStatusFlags(I2C1);
	uint8_t kk = (stats & 0x20);
	if(kk)
		return;

	LED_BLUE_TOGGLE();
	IMUpt->ClearMagOffset();
}

// SW3
void GPIOA_IRQHANDLER(){
	GPIO_PortClearInterruptFlags(GPIOA, 1 << BOARD_SW3_GPIO_PIN);
}





#if defined (__cplusplus)
} // extern "C"
#endif
