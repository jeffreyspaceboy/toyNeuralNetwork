//
//  Tensor.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 6/2/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Tensor.hpp"

//---Constructors---//
Tensor::Tensor(){} //Blank Constructor

Tensor::Tensor(float *data, Shape shape){ this->set_data(data, shape); }//Standard Constructor

Tensor::Tensor(Shape shape, bool randomize){ //Zero or Randomize Constructor
    if(randomize){
        this->set_data(this->random(-1, 1, 1000), shape);
    }else{
        this->set_data(0.0, shape);
    }
}

Tensor::Tensor(float *data, unsigned int x_size, unsigned int y_size, unsigned int z_size){ this->set_data(data, Shape(x_size,y_size,z_size)); } //Standard Constructor, using y,x size

Tensor::Tensor(unsigned int x_size, unsigned int y_size, unsigned int z_size){ this->set_data(0.0, Shape(x_size,y_size,z_size)); } //Zero Constructor, using y,x size

//---Copy Constructors---//
Tensor::Tensor(const Tensor &obj){ this->set_data(obj.data, obj.shape); }
 
//---Destructors---//
Tensor::~Tensor(void){ free(this->data); }

//---Get---//
Shape Tensor::get_shape(){ return this->shape; }
float *Tensor::get_data(){ return this->data; }
float Tensor::get_cell(Cell cell){ return this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])]; }

//---Set---//
void Tensor::set_shape(Shape shape){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data may be lost if shape does not match the original...\n");
    }
    this->shape = shape;
}

void Tensor::set_data(float *data, Shape shape){
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

void Tensor::set_data(float data, Shape shape){
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

void Tensor::set_cell(float data, Cell cell){
    this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])+(cell.d[2] * this->shape.d[0] * this->shape.d[1])] = data;
}

//---Math Operations---//
void Tensor::map(float (*func)(float val, Cell cell)){
    Cell cell;
    for(cell.d[2] = 0; cell.d[2] < this->shape.d[2]; cell.d[2]++){
        for(cell.d[1] = 0; cell.d[1] < this->shape.d[1]; cell.d[1]++){
            for(cell.d[0] = 0; cell.d[0] < this->shape.d[0]; cell.d[0]++){
                float val = this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])+(cell.d[2] * this->shape.d[0] * this->shape.d[1])];
                this->data[cell.d[0]+(cell.d[1] * this->shape.d[0])+(cell.d[2] * this->shape.d[0] * this->shape.d[1])] = (*func)(val,cell);
            }
        }
    }
}

Tensor *Tensor::map(Tensor *a, float (*func)(float val, Cell cell)){
    Cell cell;
    for(cell.d[2] = 0; cell.d[2] < this->shape.d[2]; cell.d[2]++){
        for(cell.d[1] = 0; cell.d[1] < this->shape.d[1]; cell.d[1]++){
            for(cell.d[0] = 0; cell.d[0] < this->shape.d[0]; cell.d[0]++){
                float val = a->data[cell.d[0]+(cell.d[1] * this->shape.d[0])+(cell.d[2] * this->shape.d[0] * this->shape.d[1])];
                a->data[cell.d[0]+(cell.d[1] * this->shape.d[0])+(cell.d[2] * this->shape.d[0] * this->shape.d[1])] = (*func)(val,cell);
            }
        }
    }
    return a;
}


void Tensor::add(Tensor &obj){
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] + obj.data[i];
    }
}

void Tensor::add(float obj){
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] + obj;
    }
}

void Tensor::subtract(Tensor &obj){
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] - obj.data[i];
    }
}

void Tensor::subtract(float obj){
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] - obj;
    }
}

void Tensor::hadamard_product(Tensor &obj){
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] * obj.data[i];
    }
}

void Tensor::scalar_product(float obj){
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = this->data[i] * obj;
    }
}

Tensor Tensor::operator +(Tensor &obj){ //Overloading add operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] + obj.data[i];
    }
    return Tensor(new_data, this->shape);
}

Tensor Tensor::operator -(Tensor &obj){ //Overloading subtract operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] - obj.data[i];
    }
    return Tensor(new_data, this->shape);
}

//TODO: HANDLE TENSORS FOR CROSS PRODUCT
Tensor Tensor::operator *(Tensor &obj){ //CROSS PRODUCT - overloading the * operator
    if(this->shape.d[0] != obj.shape.d[1]){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        printf("ERROR: For cross product columns of A must match rows of B.\n");
        exit(1);
    }
    Tensor result(Shape(this->shape.d[0], obj.shape.d[1]));
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

Tensor Tensor::operator ->*(Tensor &obj){ //HADAMARD PRODUCT - overloading the ->* (not sure what that is normally?) operator
    if(!(this->check_shape(obj.shape))){
        printf("ERROR: Shape of matrices must match.\n");
        exit(1);
    }
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] * obj.data[i];
    }
    return Tensor(new_data, this->shape);
}

Tensor Tensor::operator *(float obj){ //SCALAR PRODUCT - overloading the * operator
    float *new_data = (float*)(malloc((this->shape.size)*(sizeof(float))));
    for(unsigned int i = 0; i < this->shape.size; i++){
        new_data[i] = this->data[i] * obj;
    }
    return Tensor(new_data, this->shape);
}

Tensor Tensor::operator ~(){ return transposed(); }//TRANSPOSE - overloading the ~ operator

Tensor Tensor::transposed(){ //TRANSPOSE
    Cell cell;
    Tensor result(Shape(this->shape.d[1], this->shape.d[0],this->shape.d[2])); //TODO: Is it benefitial to transpose in other D than 2D
    for(cell.d[2] = 0; cell.d[2] < result.shape.d[2]; cell.d[2]++){
        for(cell.d[1] = 0; cell.d[1] < result.shape.d[1]; cell.d[1]++){
            for(cell.d[0] = 0; cell.d[0] < result.shape.d[0]; cell.d[0]++){
                result.set_cell(this->data[cell.d[1] + (cell.d[0] * result.shape.d[1])  + (cell.d[2] * this->shape.d[0] * this->shape.d[1])], cell);//TODO: CHECK IF CORRECT
            }
        }
    }
    return result;
}

float Tensor::random(int lowerBound, int upperBound, int decimal_precision){
    lowerBound = lowerBound*decimal_precision;
    upperBound = upperBound*decimal_precision;
    return ((float)(rand() % (upperBound-lowerBound+1) + lowerBound)/decimal_precision);
}

void Tensor::randomize(int lowerBound, int upperBound, int decimal_precision){ this->set_data(this->random(lowerBound, upperBound, decimal_precision), this->shape); }

void Tensor::round_to(float val){
    for(unsigned int i = 0; i < this->shape.size; i++){
        this->data[i] = floor(this->data[i] * val + 0.5)/val;
    }
}

//---Activation Functions---//
void Tensor::sigmoid(){this->map(singleSigmoid);}
void Tensor::dSigmoid(){this->map(singleDSigmoid);}

//---Checking---//
bool Tensor::check_matrix(){
    if(this->shape.size <= 0){
        printf("ERROR: No matrix exists.");
        return false;
    }
    return true;
}

bool Tensor::check_shape(Shape shape){
    if((this->shape.d[0] != shape.d[0])||(this->shape.d[1] != shape.d[1])||(this->shape.d[2] != shape.d[2])){ return false; }
    else { return true; }
}

//---Other---//
void Tensor::print(){
    Cell cell;
    printf("::{\n");
    for(cell.d[2] = 0; cell.d[2] < this->shape.d[2]; cell.d[2]++) {
        printf("Layer: %d\n", cell.d[2]);
        for(cell.d[1] = 0; cell.d[1] < this->shape.d[1]; cell.d[1]++) {
            printf("[");
            for(cell.d[0] = 0; cell.d[0] < this->shape.d[0]-1; cell.d[0]++){
                printf("%f,",data[cell.d[0]+(cell.d[1] * this->shape.d[0])+(cell.d[2] * this->shape.d[0] * this->shape.d[1])]);
            }
            printf("%f]\n",this->data[(this->shape.d[0]-1)+(cell.d[1] * this->shape.d[0])+(cell.d[2] * this->shape.d[0] * this->shape.d[1])]);
        }
    }
    printf("}::\n");
}


/* Formulas for regular and transposed translation
 unsigned int regular(){
     i[1]+(i[0] * this->shape[1])
 }
 unsigned int trans(){
      i[0] + (i[1] * this->shape[0])
 }
 */



