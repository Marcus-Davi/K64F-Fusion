/*
 * IMU.h
 *
 *  Created on: 13 de fev de 2020
 *      Author: marcus
 */

#ifndef IMU_H_
#define IMU_H_

#include "STBC.h" //IMU SHield
#include "Vec3.h"

class IMU {
public:
	IMU();
	virtual ~IMU();

private:
	const STBC* ImuShield = nullptr;

};

#endif /* IMU_H_ */
