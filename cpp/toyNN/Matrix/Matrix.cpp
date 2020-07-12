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

Matrix::Matrix(float *data, Shape shape){ this->set_data(data, shape); }//Standard Constructor

Matrix::Matrix(Shape shape, bool randomize){ //Zero or Randomize Constructor
    if(randomize){
        this->set_data(this->random(-1, 1, 1000), shape);
    }else{
        this->set_data(0.0, shape);
    }
}

Matrix::Matrix(float *data, unsigned int x_size, unsigned int y_size){ this->set_data(data, Shape(x_size,y_size)); } //Standard Constructor, using y,x size

Matrix::Matrix(unsigned int x_size, unsigned int y_size){ this->set_data(0.0, Shape(x_size,y_size)); } //Zero Constructor, using y,x size

//---Copy Constructors---//
Matrix::Matrix(const Matrix &obj){ this->set_data(obj.data, obj.shape); }
 
//---Destructors---//
Matrix::~Matrix(void){ free(this->data); }

//---Get---//
Shape Matrix::get_shape(){ return this->shape; }
float *Matrix::get_data(){ return this->data; }
float Matrix::get_cell(Cell cell){ return this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])]; }

//---Set---//
void Matrix::set_shape(Shape shape){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data may be lost if shape does not match the original...\n");
    }
    this->shape = shape;
}

void Matrix::set_data(float *data, Shape shape){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data is being cleared...\n");
        free(this->data);
    }
    if(!(this->check_shape(shape))){
        this->set_shape(shape);
    }
    this->data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = data[i];
    }
}

void Matrix::set_data(float data, Shape shape){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data is being cleared...\n");
        free(this->data);
    }
    if(!(this->check_shape(shape))){
        this->set_shape(shape);
    }
    this->data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = data;
    }
}

void Matrix::set_cell(float data, Cell cell){
    this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])] = data;
}

//---Math Operations---//
void Matrix::map(float (*func)(float val, Cell cell)){
    Cell cell;
    for(cell.d[1] = 0; cell.d[1] < this->shape.d[1]; cell.d[1]++){
        for(cell.d[0] = 0; cell.d[0] < this->shape.d[0]; cell.d[0]++){
            float val = this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])];
            this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])] = (*func)(val,cell);
        }
    }
}

Matrix *Matrix::map(Matrix *a, float (*func)(float val, Cell cell)){
    Cell cell;
    for(cell.d[1] = 0; cell.d[1] < this->shape.d[1]; cell.d[1]++){
        for(cell.d[0] = 0; cell.d[0] < this->shape.d[0]; cell.d[0]++){
            float val = a->data[cell.d[0]+(cell.d[1] * this->shape.d[0])];
            a->data[cell.d[0]+(cell.d[1] * this->shape.d[0])] = (*func)(val,cell);
        }
    }
    return a;
}


void Matrix::add(Matrix &obj){
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] + obj.data[i];
    }
}

void Matrix::add(float obj){
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] + obj;
    }
}

void Matrix::subtract(Matrix &obj){
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] - obj.data[i];
    }
}

void Matrix::subtract(float obj){
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] - obj;
    }
}

void Matrix::hadamard_product(Matrix &obj){
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] * obj.data[i];
    }
}

void Matrix::scalar_product(float obj){
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] * obj;
    }
}

Matrix Matrix::operator +(Matrix &obj){ //Overloading add operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] + obj.data[i];
    }
    return Matrix(new_data, this->shape);
}

Matrix Matrix::operator -(Matrix &obj){ //Overloading subtract operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] - obj.data[i];
    }
    return Matrix(new_data, this->shape);
}

Matrix Matrix::operator *(Matrix &obj){ //CROSS PRODUCT - overloading the * operator
    if(this->shape.d[0] != obj.shape.d[1]){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        printf("ERROR: For cross product columns of A must match rows of B.\n");
        exit(1);
    }
    Matrix result(Shape(this->shape.d[0], obj.shape.d[1]));
    Cell cell;
    unsigned int z;
    float sum;
    for(cell.d[1] = 0; cell.d[1] < result.shape.d[1]; cell.d[1]++){
        for(cell.d[0] = 0; cell.d[0] < result.shape.d[0]; cell.d[0]++){
            sum = 0;
            for(z = 0; z < this->shape.d[0]; z++){
                sum += this->data[(cell.d[1] * this->shape.d[0]) + z] * obj.data[(z * result.shape.d[0]) + cell.d[0]]; //OLD VERSION: sum += this->getData(y,z) * obj.data(z,x);
                }//Preforming cross product
            result.set_cell(sum,cell);
        }
    }
    return result;
}

Matrix Matrix::operator ->*(Matrix &obj){ //HADAMARD PRODUCT - overloading the ->* (not sure what that is normally?) operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] * obj.data[i];
    }
    return Matrix(new_data, this->shape);
}

Matrix Matrix::operator *(float obj){ //SCALAR PRODUCT - overloading the * operator
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] * obj;
    }
    return Matrix(new_data, this->shape);
}

Matrix Matrix::operator ~(){ return transposed(); }//TRANSPOSE - overloading the ~ operator

Matrix Matrix::transposed(){ //TRANSPOSE
    Cell cell;
    Matrix result(Shape(this->shape.d[1], this->shape.d[0]));
    for(cell.d[1] = 0; cell.d[1] < result.shape.d[1]; cell.d[1]++){
        for(cell.d[0] = 0; cell.d[0] < result.shape.d[0]; cell.d[0]++){
            result.set_cell(this->data[(cell.d[0] * result.shape.d[1]) + cell.d[1]], cell);
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
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = floor(this->data[i] * val + 0.5)/val;
    }
}

//---Activation Functions---//
void Matrix::sigmoid(){this->map(singleSigmoid);}
void Matrix::dSigmoid(){this->map(singleDSigmoid);}

//---Checking---//
bool Matrix::check_matrix(){
    if(this->shape.size <= 0){
        printf("ERROR: No matrix exists.");
        return false;
    }
    return true;
}

bool Matrix::check_shape(Shape shape){
    if((this->shape.d[0] != shape.d[0])||(this->shape.d[1] != shape.d[1])){ return false; }
    else { return true; }
}

//---Other---//
void Matrix::print(){
    unsigned int i[2];
    for(i[1] = 0; i[1] < this->shape.d[1]; i[1]++){
        printf("[");
        for(i[0] = 0; i[0] < (this->shape.d[0]-1); i[0]++){
            printf("%lf,",this->data[i[0] + (i[1] * this->shape.d[0])]);
        }
        printf("%lf]\n",this->data[(this->shape.d[0]-1) + (i[1] * this->shape.d[0])]);
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
