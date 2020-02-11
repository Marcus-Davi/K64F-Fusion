/*
 * Matrix.cpp
 *
 *  Created on: 25 de set de 2019
 *      Author: marcus
 */

#include <Matrix.h>



Matrix::Matrix(int rows,int columns){
	this->rows = rows;
	this->columns = columns;
	this->data = new float[rows*columns];
	arm_mat_init_f32(&M, rows, columns, this->data);
	memset(data,0,rows*columns*sizeof(float));


}

Matrix::Matrix(int rows,int columns,float* data){
	this->rows = rows;
	this->columns = columns;
	this->data = data; //Talvez ñ seja mt inteligente isso aqui
	arm_mat_init_f32(&M, rows, columns, this->data);


}

Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
	delete[] this->data;
}

void Matrix::Print(){
	for(int i=0;i<rows;i++){
		PRINTF("[  ");
		for(int j=0;j<columns;j++)
		PRINTF("%f ",data[columns*i + j]);
		PRINTF("]\n\r");
	}
	PRINTF("\n\r");
}

//Seta valor da linha "i" e coluna "j" como "value"
void Matrix::SetValue(int i,int j,float value){
	this->data[columns*i + j] = value;
}

void Matrix::SetValues(const float* values){
	for(int i=0;i<rows*columns;++i)
		data[i] = values[i];
}

arm_status Matrix::Add(Matrix const& A,Matrix const&B,Matrix &Res){
	return arm_mat_add_f32(&A.M, &B.M, &Res.M);
}

arm_status Matrix::Sub(Matrix const& A,Matrix const&B,Matrix &Res){
	return arm_mat_sub_f32(&A.M, &B.M, &Res.M);
}

arm_status Matrix::Scale(Matrix const& A,Matrix &B,float k){
	return arm_mat_scale_f32(&A.M, k, &B.M);
}

arm_status Matrix::Mult(Matrix const& A,Matrix const&B,Matrix &Res){
	return arm_mat_mult_f32(&A.M, &B.M, &Res.M);
}

arm_status Matrix::Transpose(Matrix const& A,Matrix &Res){
	return arm_mat_trans_f32(&A.M, &Res.M);
}

arm_status Matrix::Inverse(Matrix const& A,Matrix &Res){
	//Aqui a matriz A é perdida, infelizmente. Bug da biblioteca.
	return arm_mat_inverse_f32(&A.M, &Res.M);
}

void Matrix::Copy(Matrix const& A,Matrix &B){
	int size = A.rows*A.columns;
	for(int i=0;i<size;++i)
		B.data[i] = A.data[i];

}
