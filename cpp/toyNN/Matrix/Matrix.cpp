//
//  Matrix.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//
#include "Matrix.hpp"

//---Constructors---//
Matrix::Matrix(){} //Standard Constructor

Matrix::Matrix(double *data, unsigned int shape[2]){ this->set_data(data, shape); }

Matrix::Matrix(unsigned int shape[2], bool randomize){
    if(randomize){
        this->set_data(this->random(-1, 1), shape);
    }else{
        this->set_data(0.0, shape);
    }
}

Matrix::Matrix(unsigned int y_size, unsigned int x_size){
    unsigned int new_shape[2] = {y_size,x_size};
    this->set_data(0.0, new_shape);
}

//---Copy Constructors---//
Matrix::Matrix(const Matrix &obj){
    unsigned int newShape[2] = {obj.shape[0],obj.shape[1]};
    this->set_shape(newShape);
    this->data = (double*)(malloc((this->size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = obj.data[i];
    }
}
 
//---Destructors---//
Matrix::~Matrix(void){ free(this->data); }

//---Get---//
unsigned int *Matrix::get_shape(){ return this->shape; }
unsigned int Matrix::get_size(){ return this->size; }
double *Matrix::get_data(){ return this->data; }
double Matrix::get_data(unsigned int cell[2]){
    //TODO: CHECK FORMULA FOR X/Y. IT IS USED OTHER PLACES TOO.
    printf("DEV WARNING: Check x,y formula\n");
    return this->data[cell[1]+(cell[0] * this->shape[1])];
}

//---Set---//
void Matrix::set_shape(unsigned int shape[2]){
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data may be lost if total size does not match the original...\n");
    }
    for(uint8_t i=0; i <= 1; i++){
        this->shape[i] = shape[i];
    }
    this->size = (this->shape[0] * this->shape[1]);
}

void Matrix::set_data(double *data, unsigned int shape[2]){
    if(this->shape[0] != shape[0] || this->shape[1] != shape[1]){
        this->set_shape(shape);
    }
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data is being cleared...\n");
        free(this->data);
    }
    this->data = (double*)(malloc((this->size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = data[i];
    }
}

void Matrix::set_data(double data, unsigned int shape[2]){
    if(this->shape[0] != shape[0] || this->shape[1] != shape[1]){
        this->set_shape(shape);
    }
    if(this->data != NULL){
        printf("WARNING: This matrix contains data! The data is being cleared...\n");
        free(this->data);
    }
    this->data = (double*)(malloc((this->size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = data;
    }
}

void Matrix::set_cell(double data, unsigned int cell[2]){
    this->data[cell[1]+(cell[0] * this->shape[1])] = data;
}

//---Math Operations---//
void Matrix::map(double (*func)(double val, unsigned int cell[2])){
    unsigned int i[2];
    for(i[0] = 0; i[0] < this->shape[0]; i[0]++){
        for(i[1] = 0; i[1] < this->shape[1]; i[1]++){
            double val = this->data[i[1]+(i[0] * this->shape[1])];
            this->data[i[1]+(i[0] * this->shape[1])] = (*func)(val,i);
        }
    }
}

Matrix *Matrix::map(Matrix *a, double (*func)(double val, unsigned int cell[2])){
    unsigned int i[2];
    for(i[0] = 0; i[0] < this->shape[0]; i[0]++){
        for(i[1] = 0; i[1] < this->shape[1]; i[1]++){
            double val = a->data[i[1]+(i[0] * this->shape[1])];
            a->data[i[1]+(i[0] * this->shape[1])] = (*func)(val,i);
        }
    }
    return a;
}

Matrix Matrix::operator +(Matrix &obj){ //Overloading add operator
    if((this->shape[0] != obj.shape[0])||(this->shape[1] != obj.shape[1])){ //Check matrix dimensions.
        printf("ERROR: Columns and rows must match.\n");
        exit(1);
    }else{ //If matrix dimensions match, then do add.
        double *new_data = (double*)(malloc((this->size)*(sizeof(double))));
        for(unsigned int i = 0; i < this->size; i++){
            new_data[i] = this->data[i] + obj.data[i];
        }
        return Matrix(new_data, this->shape);
    }
}

Matrix Matrix::operator -(Matrix &obj){ //Overloading subtract operator
    if((this->shape[0] != obj.shape[0])||(this->shape[1] != obj.shape[1])){ //Check matrix dimensions.
        printf("ERROR: Columns and rows must match.\n");
        exit(1);
    }else{ //If matrix dimensions match, then do add.
        double *new_data = (double*)(malloc((this->size)*(sizeof(double))));
        for(unsigned int i = 0; i < this->size; i++){
            new_data[i] = this->data[i] - obj.data[i];
        }
        return Matrix(new_data, this->shape);
    }
}

Matrix Matrix::operator *(Matrix &obj){ //CROSS PRODUCT - overloading the * operator
    if(this->shape[1] != obj.shape[0]){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        printf("ERROR: For cross product columns of A must match rows of B.\n");
        exit(1);
    }else{
        Matrix result(this->shape[0], obj.shape[1]);
        unsigned int i[2];
        unsigned int z;
        double sum;
        for(i[0] = 0; i[0] < result.shape[0]; i[0]++){
            for(i[1] = 0; i[1] < result.shape[1]; i[1]++){
                sum = 0;
                for(z = 0; z < this->shape[1]; z++){
                    sum += this->data[(i[0] * this->shape[1]) + z] * obj.data[(z * result.shape[1]) + i[1]]; //OLD VERSION: sum += this->getData(y,z) * obj.data(z,x);
                    }//Preforming cross product
                result.set_data(sum,i);
            }
        }
        return result; //Return the new 2D vector
    }
}

Matrix Matrix::operator ->*(Matrix &obj){ //HADAMARD PRODUCT - overloading the ->* (not sure what that is normally?) operator
    if(this->shape[0] != obj.shape[0] || this->shape[1] != obj.shape[1]){
        printf("ERROR: Size of matrices Must match.\n");
        exit(1);
    }
    Matrix result(this->shape[0],obj.shape[1]);
    for(unsigned int i = 0; i < this->size; i++){
        result.data[i] = this->data[i] * obj.data[i];
    }
    return result;
}

Matrix Matrix::operator *(double obj){ //SCALAR PRODUCT - overloading the * operator
    Matrix result(this->shape[0],this->shape[1]);
    for(unsigned int i = 0; i < this->size; i++){
        result.data[i] = this->data[i]*obj; //Just muliply ever matrix element by the double
    }
    return result;
}

Matrix Matrix::transposed(){ //TRANSPOSE - overloading the ~ operator
    unsigned int i[2];
    unsigned int new_shape[2] = {this->shape[1], this->shape[0]};
    Matrix result(new_shape[1],new_shape[0]);
    for(i[0] = 0; i[0] < new_shape[1]; i[0]++){
        for(i[1] = 0; i[1] < new_shape[0]; i[1]++){
            result.set_data(this->data[(i[1] * result.shape[0]) + i[0]], i);
        }
    }
    return result;
}

double Matrix::random(int lowerBound, int upperBound){
    lowerBound = lowerBound*1000;
    upperBound = upperBound*1000;
    return ((double)(rand() % (upperBound-lowerBound+1) + lowerBound)/1000);
}

void Matrix::randomize(int lowerBound, int upperBound){
    lowerBound = lowerBound*1000;
    upperBound = upperBound*1000;
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = (double)(rand() % (upperBound-lowerBound+1) + lowerBound)/1000;
    }
}

void Matrix::round_to(double val){
    for(unsigned int i = 0; i < this->size; i++){
        this->data[i] = floor(this->data[i] * val + 0.5)/val;
    }
}

//---Activation Functions---//
double singleSigmoid(double val, unsigned int cell[2]){return (1/(1+(exp(-val))));}
void Matrix::sigmoid(){this->map(singleSigmoid);}
double singleDSigmoid(double val, unsigned int cell[2]){return (singleSigmoid(val, cell)*(1-singleSigmoid(val, cell)));}
void Matrix::dSigmoid(){this->map(singleDSigmoid);}

//---Other---//
bool Matrix::checkMatrix(){
    if(this->size <= 0){
        std::cout<<"ERROR: No matrix exists."<<std::endl;
        return false;
    }
    return true;
}

void Matrix::print(){
    unsigned int y,x;
    for(y = 0; y < this->shape[0]; y++){
        printf("[");
        for(x = 0; x < (this->shape[1]-1); x++){
            printf("%lf,",this->data[x + (y * this->shape[1])]);
        }
        printf("%lf]\n",this->data[(this->shape[1]-1) + (y * this->shape[1])]);
    }
}
