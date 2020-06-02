//
//  Matrix.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//
#include "Matrix.hpp"

//---Constructors---//
Matrix::Matrix(unsigned long int rows, unsigned long int cols){ //Constructor (fills size with 0's)
    for(int y=0;y<(rows);y++){ //Fill this->data vector with all 0's in size of rows and cols
        std::vector<double> temp;
        for(int x=0;x<(cols);x++){ temp.push_back(0); }
        this->data.push_back(temp);
    }
}
Matrix::Matrix(std::vector<std::vector<double>> newData){ this->data = newData; } //Fills data with a 2D vector.
Matrix::Matrix(){} //Standard Constructor

//---Copy Constructors---//
Matrix::Matrix(const Matrix &obj){ this->data = obj.data; } //Copy constructor

//---Destructors---//
Matrix::~Matrix(void){}

//---Get---//
unsigned long int Matrix::getNumRows(){ return this->data.size(); }
unsigned long int Matrix::getNumCols(){
    if(this->data.size()>0){ return this->data[0].size(); }
    else{
        std::cout<<"ERROR: Nothing in Matrix"<<std::endl;
        exit(1);
    }
}
std::vector<std::vector<double>> Matrix::getData(){ return this->data; }
double Matrix::getData(int y, int x){ return this->data[y][x]; }

//---Set---//
void Matrix::setData(int y, int x, double newData){ this->data[y][x] = newData; }

//---Math Operations---//
void Matrix::map(double (*func)(double val,int y,int x)){
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = this->data[y][x];
            this->data[y][x] = (*func)(val,y,x);
        }
    }
}

Matrix Matrix::map(Matrix a, double (*func)(double val,int y,int x)){
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = a.data[y][x];
            a.data[y][x] = (*func)(val,y,x);
        }
    }
    return a;
}

Matrix Matrix::operator +(Matrix &obj){ //Overloading add operator
    if((this->getNumRows() != obj.getNumRows())||(this->getNumCols() != obj.getNumCols())){ //Check matrix dimensions.
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{ //If matrix dimensions match, then do add.
        Matrix result;
        for(int y=0;y<this->getNumRows();y++){
            std::vector<double> temp;
            for(int x=0;x<this->getNumCols();x++){
                double val = this->data[y][x];
                temp.push_back(val + obj.data[y][x]); //Adding values into each location of a new vector
            }
            result.data.push_back(temp); //Adding each row to new vector
        }
        return result; //Return the new 2D vector
    }
}

Matrix Matrix::operator -(Matrix &obj){ //Overloading subtract operator
    if((this->getNumRows() != obj.getNumRows())||(this->getNumCols() != obj.getNumCols())){ //Check matrix dimensions.
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{ //If matrix dimensions match, then do subtract.
        Matrix result;
        for(int y=0;y<this->getNumRows();y++){
            std::vector<double> temp;
            for(int x=0;x<this->getNumCols();x++){
                double val = this->data[y][x];
                temp.push_back(val - obj.data[y][x]); //Subtracting values into each location of a new vector
            }
            result.data.push_back(temp); //Adding each row to new vector
        }
        return result; //Return the new 2D vector
    }
}

Matrix Matrix::operator *(Matrix &obj){ //CROSS PRODUCT - overloading the * operator
    if(this->getNumCols() != obj.getNumRows()){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        std::cout<<"ERROR: Columns of A must match rows of B."<<std::endl;
        exit(1);
    }else{
        Matrix result(this->getNumRows(),obj.getNumCols());
        for(int y=0;y<result.getNumRows();y++){
            for(int x=0;x<result.getNumCols();x++){
                double sum = 0;
                for(int z=0;z<this->getNumCols();z++){ sum += this->getData(y,z)*obj.getData(z,x); }//Preforming cross product
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










