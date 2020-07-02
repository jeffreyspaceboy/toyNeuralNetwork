//
//  Matrix.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//
#include "Matrix.hpp"

//---Constructors---//
Matrix::Matrix(double *data, unsigned int y_size, unsigned int x_size){ //Constructor (fills size with 0's)
    this->y_size = y_size;
    this->x_size = x_size;
    this->data_size = (y_size * x_size);
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = data[i];
    }
}

Matrix::Matrix(unsigned int y_size, unsigned int x_size, bool randomize){ //Constructor (fills size with 0's)
    this->y_size = y_size;
    this->x_size = x_size;
    this->data_size = (y_size * x_size);
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    if(randomize){
        printf("ERROR: Not randomize function built in, must add to code\n");
    }else{
        for(unsigned int i = 0; i < this->data_size; i++){
            this->data[i] = 0;
        }
    }
}

Matrix::Matrix(){ //Standard Constructor
    this->y_size = NULL;
    this->x_size = NULL;
    this->data_size = NULL;
    this->data = NULL;
}

//---Copy Constructors---//
Matrix::Matrix(const Matrix &obj){
    this->y_size = obj.y_size;
    this->x_size = obj.x_size;
    this->data_size = (obj.y_size * obj.x_size);
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = obj.data[i];
    }
}

//---Destructors---//
Matrix::~Matrix(void){ free(this->data); }

//---Get---//
unsigned int Matrix::get_y_size(){ return this->y_size; }
unsigned int Matrix::get_x_size(){ return this->x_size; }
unsigned int Matrix::get_data_size(){ return this->data_size; }
double *Matrix::get_data(){ return this->data; }
double Matrix::get_data(unsigned int y, unsigned int x){
    printf("DEVELOPER WARNING: Check x,y formula\n");
    return this->data[x+(y * this->x_size)];
}

//---Set---//
void Matrix::set_size(unsigned int y_size, unsigned int x_size){
    this->y_size = y_size;
    this->x_size = x_size;
}
void Matrix::set_data(double *data, unsigned int y_size, unsigned int x_size){
    if(this->y_size != y_size || this->x_size != x_size){
        this->y_size = y_size;
        this->x_size = x_size;
        this->data_size = (y_size * x_size);
        if(this->data != NULL){ free(this->data); }
    }
    this->data = (double*)(malloc((this->data_size)*(sizeof(double))));
    for(unsigned int i = 0; i < this->data_size; i++){
        this->data[i] = data[i];
    }
}

//---Math Operations---//
void Matrix::map(double (*func)(double val, unsigned int y, unsigned int x)){
    unsigned int x,y;
    for(y = 0; y < this->y_size; y++){
        for(x = 0; x < this->x_size; x++){
            double val = this->data[x+(y * this->x_size)];
            this->data[x+(y * this->x_size)] = (*func)(val,y,x);
        }
    }
}

Matrix *Matrix::map(Matrix *a, double (*func)(double val, unsigned int y, unsigned int x)){
    unsigned int x,y;
    for(y = 0; y < this->y_size; y++){
        for(x = 0; x < this->x_size; x++){
            double val = a->data[x+(y * this->x_size)];
            a->data[x+(y * this->x_size)] = (*func)(val,y,x);
        }
    }
    return a;
}

Matrix Matrix::operator +(Matrix &obj){ //Overloading add operator
    if((this->y_size != obj.y_size)||(this->x_size != obj.x_size)){ //Check matrix dimensions.
        printf("ERROR: Columns and Rows must match.\n");
        exit(1);
    }else{ //If matrix dimensions match, then do add.
        double *new_data = (double*)(malloc((this->data_size)*(sizeof(double))));
        for(unsigned int i = 0; i < this->data_size; i++){
            new_data[i] = this->data[i] + obj.data[i];
        }
        return Matrix(new_data, this->y_size, this->x_size);
    }
}

Matrix Matrix::operator -(Matrix &obj){ //Overloading subtract operator
    if((this->y_size != obj.y_size)||(this->x_size != obj.x_size)){ //Check matrix dimensions.
        printf("ERROR: Columns and Rows must match.\n");
        exit(1);
    }else{ //If matrix dimensions match, then do add.
        double *new_data = (double*)(malloc((this->data_size)*(sizeof(double))));
        for(unsigned int i = 0; i < this->data_size; i++){
            new_data[i] = this->data[i] - obj.data[i];
        }
        return Matrix(new_data, this->y_size, this->x_size);
    }
}

Matrix Matrix::operator *(Matrix &obj){ //CROSS PRODUCT - overloading the * operator
    if(this->x_size != obj.y_size){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        std::cout<<"ERROR: For Cross product columns of A must match rows of B."<<std::endl;
        exit(1);
    }else{
        Matrix result(this->getNumRows(),obj.getNumCols());
        for(int y=0;y<result.getNumRows();y++){
            for(int x=0;x<result.getNumCols();x++){
                double sum = 0;
                for(int z=0;z<this->getNumCols();z++){
                    sum += this->getData(y,z) * obj.data(z,x);
                    //sum += this->getData(y,z) * obj.data(z,x);
                    }//Preforming cross product
                result.setData(y,x,sum);
            }
        }
        return result; //Return the new 2D vector
    }
}

Matrix Matrix::operator ->*(Matrix &obj){ //HADAMARD PRODUCT - overloading the ->* (not sure what that is normally?) operator
    if(this->getNumRows() == obj.getNumRows() && this->getNumCols() == obj.getNumCols()){
        Matrix result(this->getNumRows(),obj.getNumCols());
        for(int y=0;y<getNumRows();y++){
            for(int x=0;x<getNumCols();x++){
                double val = this->data[y][x];
                result.data[y][x] = val*obj.data[y][x];
            }
        }
        return result;
    }else{
        std::cout<<"ERROR: Size of matrices Must match."<<std::endl;
        exit(1);
    }
}

Matrix Matrix::operator *(double &obj){ //SCALAR PRODUCT - overloading the * operator
    Matrix result(this->getNumRows(),this->getNumCols());
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = this->data[y][x];
            result.data[y][x] = val*obj; //Just muliply ever matrix element by the double
        }
    }
    return result;
}

Matrix Matrix::transposed(){ //TRANSPOSE - overloading the ~ operator
    unsigned long int numRows = this->getNumCols();
    unsigned long int numCols = this->getNumRows();
    Matrix result(numRows,numCols);
    std::vector<std::vector<double>> newMatrix;
    for(int y=0;y<numRows;y++){
        for(int x=0;x<numCols;x++){ result.setData(y, x, this->data[x][y]); }
    }
    return result;
}

void Matrix::randomize(int lowerBound, int upperBound){
    lowerBound = lowerBound*100;
    upperBound = upperBound*100;
    for(int y=0;y<(this->getNumRows());y++){
        for(int x=0;x<(this->getNumCols());x++){ this->data[y][x] = (double)(rand() % (upperBound-lowerBound+1) + lowerBound)/100; }
    }
}

void Matrix::roundTo(double val){
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){ this->data[y][x] = floor(this->data[y][x] * val + 0.5)/val; }
    }
}

//---Activation Functions---//
double singleSigmoid(double val, int y, int x){return (1/(1+(exp(-val))));}
void Matrix::sigmoid(){this->map(singleSigmoid);}
double singleDSigmoid(double val, int y, int x){return (singleSigmoid(val, y, x)*(1-singleSigmoid(val, y, x)));}
void Matrix::dSigmoid(){this->map(singleDSigmoid);}

//---Other---//
void Matrix::checkMatrix(){
    if(this->data.size()<0){
        std::cout<<"ERROR: No matrix exists."<<std::endl;
        exit(1);
    }
}

void Matrix::print(){
    for(int y=0;y<this->getNumRows();y++){
        std::cout<<"[";
        for(int x=0;x<(this->getNumCols()-1);x++){ std::cout<<this->data[y][x]<<","; }
        std::cout<<this->data[y][getNumCols()-1]<<"]"<<std::endl;
    }
}










