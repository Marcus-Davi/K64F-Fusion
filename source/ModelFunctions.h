/*
 * SystemFunctions.h
 *
 *  Created on: 17 de fev de 2020
 *      Author: marcus
 */

#ifndef MODELFUNCTIONS_H_
#define MODELFUNCTIONS_H_

#include "arm_math.h"
#include "EKF.h"
#include "Quaternion.h"
#define SystemTs 0.02f

static float mag_field;


// TODO Pensar numa forma melhor de implementar funções. Usar prototipo fornecido pela classe ?

namespace AttitudeEstimation {


static void StateJacobian(const float* Xk,const float *Uk,void* Res){
	arm_matrix_instance_f32* M = (arm_matrix_instance_f32*)Res;

	M->pData[0] = 1.0f;
	M->pData[1] = -Uk[0]*SystemTs/2;
	M->pData[2] = -Uk[1]*SystemTs/2;
	M->pData[3] = -Uk[2]*SystemTs/2;

	M->pData[4] = Uk[0]*SystemTs/2;
	M->pData[5] = 1.0f;
	M->pData[6] = Uk[2]*SystemTs/2;
	M->pData[7] = -Uk[1]*SystemTs/2;

	M->pData[8] = Uk[1]*SystemTs/2;
	M->pData[9] = -Uk[2]*SystemTs/2;
	M->pData[10] = 1.0f;
	M->pData[11] = Uk[0]*SystemTs/2;

	M->pData[12] = Uk[2]*SystemTs/2;
	M->pData[13] = Uk[1]*SystemTs/2;
	M->pData[14] = -Uk[0]*SystemTs/2;
	M->pData[15] = 1.0f;

}


static void MeasurementJacobian(const float* Xk,const float *Uk,void* Res){
	arm_matrix_instance_f32* M = (arm_matrix_instance_f32*)Res;

	float m = mag_field*0.9440f; // B * cos(m_incl)
	float n = mag_field*0.3298f; // B * sin(m_incl)

	static const float g = 9.8;

	M->pData[0] = -Xk[2]*g;
	M->pData[1] = Xk[3]*g;
	M->pData[2] = -Xk[0]*g;
	M->pData[3] = Xk[1]*g;


	M->pData[4] = Xk[1]*g;
	M->pData[5] = Xk[0]*g;
	M->pData[6] = Xk[3]*g;
	M->pData[7] = Xk[2]*g;


	M->pData[8] = Xk[0]*g;
	M->pData[9] = -Xk[1]*g;
	M->pData[10] = -Xk[2]*g;
	M->pData[11] = Xk[3]*g;


	M->pData[12] = Xk[0]*m + (-Xk[2]*n);
	M->pData[13] = Xk[1]*m + (Xk[3]*n);
	M->pData[14] = -Xk[2]*m + (-Xk[0]*n);
	M->pData[15] = -Xk[3]*m + (Xk[1]*n);


	M->pData[16] = -Xk[3]*m + (Xk[1]*n);
	M->pData[17] = Xk[2]*m + (Xk[0]*n);
	M->pData[18] = Xk[1]*m + (Xk[3]*n);
	M->pData[19] = -Xk[0]*m + (Xk[2]*n);


	M->pData[20] = Xk[2]*m + (Xk[0]*n);
	M->pData[21] = Xk[3]*m + (-Xk[1]*n);
	M->pData[22] = Xk[0]*m + (-Xk[2]*n);
	M->pData[23] = Xk[1]*m + (Xk[3]*n);

	arm_mat_scale_f32(M, 2.0f, M);

}

void StateFunction(const float* Xk,const float *Uk,void* Res){
	arm_matrix_instance_f32* M = (arm_matrix_instance_f32*)Res;

	Quaternion qk(Xk[0],Xk[1],Xk[2],Xk[3]);
	Quaternion qk_w(0,Uk[0],Uk[1],Uk[2]);
	Quaternion qk1;
	qk1 = qk*qk_w;
	qk1 = qk1* (SystemTs/2);
	qk1 = qk1 + qk;


M->pData[0] = qk1.w;
M->pData[1] = qk1.v.x;
M->pData[2] = qk1.v.y;
M->pData[3] = qk1.v.z;

}

void MeasurementFunction(const float* Xk,const float *Uk,void* Res){
	arm_matrix_instance_f32* M = (arm_matrix_instance_f32*)Res;

	float m = mag_field*0.9440f; // B * cos(m_incl)
	float n = mag_field*0.3298f; // B * sin (m_incl)


	Quaternion qk(Xk[0],Xk[1],Xk[2],Xk[3]);
	Quaternion qg(0,0,0,9.8); //gravity
	Quaternion qm(0,m,0,n); //gravity
	Quaternion qa,qb;

	qa.v = qk.RotateFrame(qg.v);
	qb.v = qk.RotateFrame(qm.v);


	M->pData[0] = qa.v.x;
	M->pData[1] = qa.v.y;
	M->pData[2] = qa.v.z;
	M->pData[3] = qb.v.x;
	M->pData[4] = qb.v.y;
	M->pData[5] = qb.v.z;

}

}


#endif /* MODELFUNCTIONS_H_ */
