/*
 * FXOS.h
 *
 *  Created on: 11 de fev de 2020
 *      Author: marcus
 */

#ifndef IMU_H_
#define IMU_H_

#define IMU_I2C I2C1


/*Registradores*/
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


#endif /* IMU_H_ */
