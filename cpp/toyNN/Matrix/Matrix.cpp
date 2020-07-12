//
//  Matrix.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//
#include "Matrix.hpp"

//---Constructors---//
Matrix::Matrix(){} //Blank Constructor

Matrix::Matrix(float *data, unsigned int shape[2]){ this->set_data(data, shape); } //Standard Constructor

Matrix::Matrix(unsigned int shape[2], bool randomize){ //Zero or Randomize Constructor
    if(randomize){
        this->set_data(this->random(-1, 1, 1000), shape);
    }else{
        this->set_data(0.0, shape);
    }
}

Matrix::Matrix(float *data, unsigned int y_size, unsigned int x_size){  //Standard Constructor, using y,x size
    unsigned int new_shape[2] = {y_size,x_size};
    this->set_data(data, new_shape);
}

Matrix::Matrix(unsigned int y_size, unsigned int x_size){ //Zero Constructor, using y,x size
    unsigned int new_shape[2] = {y_size,x_size};
    this->set_data(0.0, new_shape);
}

//---Copy Constructors---//
Matrix::Matrix(const Matrix &obj){
    unsigned int newShape[2] = {obj.shape[0],obj.shape[1]};
    this->set_data(obj.data, newShape);
}
 
//---Destructors---//
Matrix::~Matrix(void){ free(this->data); }

//---Get---//
unsigned int *Matrix::get_shape(){ return this->shape; }
unsigned int Matrix::get_size(){ return this->size; }
float *Matrix::get_data(){ return this->data; }
float Matrix::get_cell(unsigned int cell[2]){ return this->data[cell[1]+(cell[0] * this->shape[1])]; }

//---Set---//
void Matrix::set_shape(unsigned int shape[2]){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data may be lost if shape does not match the original...\n");
    }
    for(uint8_t i=0; i <= 1; i++){
        this->shape[i] = shape[i];
    }
    this->size = (this->shape[0] * this->shape[1]);
}

void Matrix::set_data(float *data, unsigned int shape[2]){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data is being cleared...\n");
        free(this->data);
    }
    if(!(this->check_shape(shape))){
        this->set_shape(shape);
    }
    this->data = (float*)(malloc((this->size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = data[i];
    }
}

void Matrix::set_data(float data, unsigned int shape[2]){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data is being cleared...\n");
        free(this->data);
    }
    if(!(this->check_shape(shape))){
        this->set_shape(shape);
    }
    this->data = (float*)(malloc((this->size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = data;
    }
}

void Matrix::set_cell(float data, unsigned int cell[2]){
    this->data[cell[1]+(cell[0] * this->shape[1])] = data;
}

//---Math Operations---//
void Matrix::map(float (*func)(float val, unsigned int cell[2])){
    unsigned int i[2];
    for(i[0] = 0; i[0] < this->shape[0]; i[0]++){
        for(i[1] = 0; i[1] < this->shape[1]; i[1]++){
            float val = this->data[i[1]+(i[0] * this->shape[1])];
            this->data[i[1]+(i[0] * this->shape[1])] = (*func)(val,i);
        }
    }
}

Matrix *Matrix::map(Matrix *a, float (*func)(float val, unsigned int cell[2])){
    unsigned int i[2];
    for(i[0] = 0; i[0] < this->shape[0]; i[0]++){
        for(i[1] = 0; i[1] < this->shape[1]; i[1]++){
            float val = a->data[i[1]+(i[0] * this->shape[1])];
            a->data[i[1]+(i[0] * this->shape[1])] = (*func)(val,i);
        }
    }
    return a;
}

Matrix Matrix::operator +(Matrix &obj){ //Overloading add operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->size; i++){
        new_data[i] = this->data[i] + obj.data[i];
    }
    return Matrix(new_data, this->shape);
}

Matrix Matrix::operator -(Matrix &obj){ //Overloading subtract operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->size; i++){
        new_data[i] = this->data[i] - obj.data[i];
    }
    return Matrix(new_data, this->shape);
}

Matrix Matrix::operator *(Matrix &obj){ //CROSS PRODUCT - overloading the * operator
    if(this->shape[1] != obj.shape[0]){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        printf("ERROR: For cross product columns of A must match rows of B.\n");
        exit(1);
    }
    Matrix result(this->shape[0], obj.shape[1]);
    unsigned int i[2];
    unsigned int z;
    float sum;
    for(i[0] = 0; i[0] < result.shape[0]; i[0]++){
        for(i[1] = 0; i[1] < result.shape[1]; i[1]++){
            sum = 0;
            for(z = 0; z < this->shape[1]; z++){
                sum += this->data[(i[0] * this->shape[1]) + z] * obj.data[(z * result.shape[1]) + i[1]]; //OLD VERSION: sum += this->getData(y,z) * obj.data(z,x);
                }//Preforming cross product
            result.set_cell(sum,i);
        }
    }
    return result;
}

Matrix Matrix::operator ->*(Matrix &obj){ //HADAMARD PRODUCT - overloading the ->* (not sure what that is normally?) operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    Matrix result(this->shape[0],obj.shape[1]);
    for(unsigned int i = 0; i < this->size; i++){
        result.data[i] = this->data[i] * obj.data[i];
    }
    return result;
}

Matrix Matrix::operator *(float obj){ //SCALAR PRODUCT - overloading the * operator
    Matrix result(this->shape[0],this->shape[1]);
    for(unsigned int i = 0; i < this->size; i++){
        result.data[i] = this->data[i]*obj; //Just muliply ever matrix element by the float
    }
    return result;
}

Matrix Matrix::operator ~(){ return transposed(); }//TRANSPOSE - overloading the ~ operator

Matrix Matrix::transposed(){ //TRANSPOSE
    unsigned int i[2];
    unsigned int new_shape[2] = {this->shape[1], this->shape[0]};
    Matrix result(new_shape);
    for(i[0] = 0; i[0] < result.shape[0]; i[0]++){
        for(i[1] = 0; i[1] < result.shape[1]; i[1]++){
            result.set_cell(this->data[(i[1] * result.shape[0]) + i[0]], i);
        }
    }
    return result;
}

float Matrix::random(int lowerBound, int upperBound, int decimal_precision){
    lowerBound = lowerBound*decimal_precision;
    upperBound = upperBound*decimal_precision;
    return ((float)(rand() % (upperBound-lowerBound+1) + lowerBound)/decimal_precision);
}

void Matrix::randomize(int lowerBound, int upperBound, int decimal_precision){ this->set_data(this->random(lowerBound, upperBound, decimal_precision), this->shape); }

void Matrix::round_to(float val){
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = floor(this->data[i] * val + 0.5)/val;
    }
}

//---Activation Functions---//
float singleSigmoid(float val, unsigned int cell[2]){return (1/(1+(exp(-val))));}
void Matrix::sigmoid(){this->map(singleSigmoid);}
float singleDSigmoid(float val, unsigned int cell[2]){return (singleSigmoid(val, cell)*(1-singleSigmoid(val, cell)));}
void Matrix::dSigmoid(){this->map(singleDSigmoid);}

//---Checking---//
bool Matrix::check_matrix(){
    if(this->size <= 0){
        printf("ERROR: No matrix exists.");
        return false;
    }
    return true;
}

bool Matrix::check_shape(unsigned int shape[2]){
    if((this->shape[0] != shape[0])||(this->shape[1] != shape[1])){ return false; }
    else { return true; }
}

//---Other---//
void Matrix::print(){
    unsigned int i[2];
    for(i[1] = 0; i[1] < this->shape[0]; i[1]++){
        printf("[");
        for(i[0] = 0; i[0] < (this->shape[1]-1); i[0]++){
            printf("%lf,",this->data[i[0] + (i[1] * this->shape[1])]);
        }
        printf("%lf]\n",this->data[(this->shape[1]-1) + (i[1] * this->shape[1])]);
    }
}



/* Formulas for regular and transposed translation
 unsigned int regular(){
     i[1]+(i[0] * this->shape[1])
 }
 unsigned int trans(){
      i[0] + (i[1] * this->shape[0])
 }
 */
