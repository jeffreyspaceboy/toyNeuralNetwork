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

Matrix::Matrix(double *data, unsigned int data_shape[2]){
    this->data_shape[0] = data_shape[0];
    this->data_shape[1] = data_shape[1];
    this->data_size = (this->data_shape[0] * this->data_shape[1]);
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = data[i];
    }
}

Matrix::Matrix(unsigned int y_size, unsigned int x_size, bool randomize){ //Constructor (fills size with 0's)
    this->data_shape[0] = data_shape[0];
    this->data_shape[1] = data_shape[1];
    this->data_size = (this->data_shape[0] * this->data_shape[1]);
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    if(randomize){
        this->randomize(-1, 1);
    }else{
        for(unsigned int i = 0; i < this->data_size; i++){
            this->data[i] = 0;
        }
    }
}

//---Copy Constructors---//
Matrix::Matrix(const Matrix &obj){
    this->data_shape[0] = obj.data_shape[0];
    this->data_shape[1] = obj.data_shape[1];
    this->data_size = (obj.data_shape[0] * obj.data_shape[1]);
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = obj.data[i];
    }
}

//---Destructors---//
Matrix::~Matrix(void){ free(this->data); }

//---Get---//
unsigned int *Matrix::get_data_shape(){ return this->data_shape; }
unsigned int Matrix::get_data_size(){ return this->data_size; }
double *Matrix::get_data(){ return this->data; }
double Matrix::get_data(unsigned int y, unsigned int x){
    //TODO: CHECK FORMULA FOR X/Y. IT IS USED OTHER PLACES TOO.
    printf("DEVELOPER WARNING: Check x,y formula\n");
    return this->data[x+(y * this->data_shape[1])];
}

//---Set---//
void Matrix::set_size(unsigned int y_size, unsigned int x_size){
    this->data_shape[0] = y_size;
    this->data_shape[1] = x_size;
}
void Matrix::set_data(double *data, unsigned int y_size, unsigned int x_size){
    if(this->data_shape[0] != y_size || this->data_shape[1] != x_size){
        this->data_shape[0] = y_size;
        this->data_shape[1] = x_size;
        this->data_size = (y_size * x_size);
        if(this->data != NULL){ free(this->data); }
    }
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = data[i];
    }
}

void Matrix::set_data(double data, unsigned int y, unsigned int x){
    this->data[x+(y * this->data_shape[1])] = data;
}

//---Math Operations---//
void Matrix::map(double (*func)(double val, unsigned int y, unsigned int x)){
    unsigned int x,y;
    for(y = 0; y < this->data_shape[0]; y++){
        for(x = 0; x < this->data_shape[1]; x++){
            double val = this->data[x+(y * this->data_shape[1])];
            this->data[x+(y * this->data_shape[1])] = (*func)(val,y,x);
        }
    }
}

Matrix *Matrix::map(Matrix *a, double (*func)(double val, unsigned int y, unsigned int x)){
    unsigned int x,y;
    for(y = 0; y < this->data_shape[0]; y++){
        for(x = 0; x < this->data_shape[1]; x++){
            double val = a->data[x+(y * this->data_shape[1])];
            a->data[x+(y * this->data_shape[1])] = (*func)(val,y,x);
        }
    }
    return a;
}

Matrix Matrix::operator +(Matrix &obj){ //Overloading add operator
    if((this->data_shape[0] != obj.data_shape[0])||(this->data_shape[1] != obj.data_shape[1])){ //Check matrix dimensions.
        printf("ERROR: Columns and Rows must match.\n");
        exit(1);
    }else{ //If matrix dimensions match, then do add.
        double *new_data = (double*)(malloc((this->data_size)*(sizeof(double))));
        for(unsigned int i = 0; i < this->data_size; i++){
            new_data[i] = this->data[i] + obj.data[i];
        }
        return Matrix(new_data, this->data_shape[0], this->data_shape[1]);
    }
}

Matrix Matrix::operator -(Matrix &obj){ //Overloading subtract operator
    if((this->data_shape[0] != obj.data_shape[0])||(this->data_shape[1] != obj.data_shape[1])){ //Check matrix dimensions.
        printf("ERROR: Columns and Rows must match.\n");
        exit(1);
    }else{ //If matrix dimensions match, then do add.
        double *new_data = (double*)(malloc((this->data_size)*(sizeof(double))));
        for(unsigned int i = 0; i < this->data_size; i++){
            new_data[i] = this->data[i] - obj.data[i];
        }
        return Matrix(new_data, this->data_shape[0], this->data_shape[1]);
    }
}

Matrix Matrix::operator *(Matrix &obj){ //CROSS PRODUCT - overloading the * operator
    if(this->data_shape[1] != obj.data_shape[0]){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        std::cout<<"ERROR: For Cross product columns of A must match rows of B."<<std::endl;
        exit(1);
    }else{
        Matrix result(this->data_shape[0],obj.data_shape[1]);
        unsigned int y,x,z;
        double sum;
        for(y = 0; y < result.data_shape[0]; y++){
            for(x = 0; x < result.data_shape[1]; x++){
                sum = 0;
                for(z = 0; z < this->data_shape[1]; z++){
                    sum += this->data[(y * this->data_shape[1]) + z] * obj.data[(z * result.data_shape[1]) + x];
                    //sum += this->getData(y,z) * obj.data(z,x);
                    }//Preforming cross product
                result.set_data(sum,y,x);
            }
        }
        return result; //Return the new 2D vector
    }
}

Matrix Matrix::operator ->*(Matrix &obj){ //HADAMARD PRODUCT - overloading the ->* (not sure what that is normally?) operator
    if(this->data_shape[0] != obj.data_shape[0] || this->data_shape[1] != obj.data_shape[1]){
        std::cout<<"ERROR: Size of matrices Must match."<<std::endl;
        exit(1);
    }
    Matrix result(this->data_shape[0],obj.data_shape[1]);
    for(unsigned int i = 0; i < this->data_size; i++){
        result.data[i] = this->data[i] * obj.data[i];
    }
    return result;
}

Matrix Matrix::operator *(double obj){ //SCALAR PRODUCT - overloading the * operator
    Matrix result(this->data_shape[0],this->data_shape[1]);
    for(unsigned int i = 0; i < this->data_size; i++){
            result.data[i] = this->data[i]*obj; //Just muliply ever matrix element by the double
    }
    return result;
}

Matrix Matrix::transposed(){ //TRANSPOSE - overloading the ~ operator
    unsigned int y,x,new_y_size,new_x_size;
    new_y_size = this->data_shape[1];
    new_x_size = this->data_shape[0];
    Matrix result(new_y_size,new_x_size);
    for(y = 0; y < new_y_size; y++){
        for(x = 0; x < new_x_size; x++){
            result.set_data(this->data[(x * result.data_shape[0]) + y], y, x);
        }
    }
    return result;
}

void Matrix::randomize(int lowerBound, int upperBound){
    lowerBound = lowerBound*1000;
    upperBound = upperBound*1000;
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = (double)(rand() % (upperBound-lowerBound+1) + lowerBound)/1000;
    }
}

void Matrix::round_to(double val){
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = floor(this->data[i] * val + 0.5)/val;
    }
}

//---Activation Functions---//
double singleSigmoid(double val, unsigned int y, unsigned int x){return (1/(1+(exp(-val))));}
void Matrix::sigmoid(){this->map(singleSigmoid);}
double singleDSigmoid(double val, unsigned int y, unsigned int x){return (singleSigmoid(val, y, x)*(1-singleSigmoid(val, y, x)));}
void Matrix::dSigmoid(){this->map(singleDSigmoid);}

//---Other---//
bool Matrix::checkMatrix(){
    if(this->data_size <= 0){
        std::cout<<"ERROR: No matrix exists."<<std::endl;
        return false;
    }
    return true;
}

void Matrix::print(){
    unsigned int y,x;
    for(y = 0; y < this->data_shape[0]; y++){
        printf("[");
        for(x = 0; x < (this->data_shape[1]-1); x++){
            printf("%lf,",this->data[x + (y * this->data_shape[1])]);
        }
        printf("%lf]\n",this->data[(this->data_shape[1]-1) + (y * this->data_shape[1])]);
    }
}
