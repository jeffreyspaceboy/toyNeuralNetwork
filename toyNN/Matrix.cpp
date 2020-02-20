//
//  Matrix.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(){} //Standard Constructor

Matrix::Matrix(std::vector<std::vector<double>> newData){ this->data = newData; } //Constructor (fills with 2D vector)

Matrix::Matrix(unsigned long int rows, unsigned long int cols){ //Constructor (fills size with 0's)
    for(int y=0;y<(rows);y++){
        std::vector<double> temp;
        for(int x=0;x<(cols);x++){
            temp.push_back(0);
        }
        this->data.push_back(temp);
    }
}

Matrix::Matrix(const Matrix &obj){ this->data = obj.data; } //Copy constructor

Matrix::~Matrix(void){} //Destructor

//Fills Data vector with vector data
void Matrix::fillFrom(std::vector<std::vector<double>> &vect){
    for(int y=0;y<(this->getNumRows());y++){
        for(int x=0;x<(this->getNumCols());x++){
            this->data[y][x] = vect[y][x];
        }
    }
}

void Matrix::randomize(int lowerBound, int upperBound){
    lowerBound = lowerBound*10;
    upperBound = upperBound*10;
    for(int y=0;y<(this->getNumRows());y++){
        for(int x=0;x<(this->getNumCols());x++){
            this->data[y][x] = (double)(rand() % (upperBound-lowerBound+1) + lowerBound)/10;
        }
    }
    //this->print();
}


unsigned long int Matrix::getNumRows(){
    return this->data.size();
}

unsigned long int Matrix::getNumCols(){
    if(this->data.size()>0){
        return this->data[0].size();
    }else{
        std::cout<<"ERROR: Nothing in Matrix"<<std::endl;
        exit(1);
    }
}

double Matrix::getData(int y, int x){
    return this->data[y][x];
}

std::vector<std::vector<double>> Matrix::getData(){
    return this->data;
}

void Matrix::setData(int y, int x, double newData){
    this->data[y][x] = newData;
}



//Prints out the matrix
void Matrix::print(){
    //std::cout<<"-------------------v"<<std::endl;
    for(int y=0;y<this->getNumRows();y++){
        std::cout<<"[";
        for(int x=0;x<(this->getNumCols()-1);x++){
            std::cout<<this->data[y][x]<<",";
        }
        std::cout<<this->data[y][getNumCols()-1]<<"]"<<std::endl;
    }
    //std::cout<<"-------------------^"<<std::endl;
}


double singleSigmoid(double val, int y, int x){
    return (1/(1+(exp(-val))));
}
double singleDSigmoid(double val, int y, int x){
    double sig = singleSigmoid(val, y, x);
    return (sig*(1-sig));
}

void Matrix::map(double (*func)(double val,int y,int x)){
    this->checkMatrix();
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = this->data[y][x];
            this->data[y][x] = (*func)(val,y,x);
        }
    }
}

Matrix Matrix::map(Matrix &a, double (*func)(double val,int y,int x)){
    Matrix result;
    result = a;
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = result.data[y][x];
            result.data[y][x] = (*func)(val,y,x);
        }
    }
    return result;
}

void Matrix::sigmoid(){
    this->map(singleSigmoid);
}
void Matrix::dSigmoid(){
    this->map(singleDSigmoid);
}

void Matrix::add(Matrix b){
    this->checkMatrix();
    //this->print();
    //b.print();
    if((this->getNumRows() != b.getNumRows())&&(this->getNumCols() != b.getNumCols())){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        for(int y=0;y<getNumRows();y++){
            for(int x=0;x<getNumCols();x++){
                double val = this->data[y][x];
                this->data[y][x] = val + b.data[y][x];
            }
        }
    }
}

void Matrix::vectorSum(Matrix &b){
    this->checkMatrix();
    //this->print();
    //b.print();
    if((this->getNumRows() != b.getNumRows())||(b.getNumCols() != 1)){
        std::cout<<"ERROR: Rows must match."<<std::endl;
        exit(1);
    }else{
        for(int y=0;y<getNumRows();y++){
            for(int x=0;x<getNumCols();x++){
                double val = this->data[y][x];
                this->data[y][x] = val + b.data[y][1];
            }
        }
    }
}

void Matrix::add(double b){
    this->checkMatrix();
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = this->data[y][x];
            this->data[y][x] = val+b;
        }
    }
}

void Matrix::subtract(Matrix b){
    this->checkMatrix();
    if((this->getNumRows() != b.getNumRows())||(this->getNumCols() != b.getNumCols())){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        return;
    }else{
        for(int y=0;y<getNumRows();y++){
            for(int x=0;x<getNumCols();x++){
                double val = this->data[y][x];
                this->data[y][x] = val - b.data[y][x];
            }
        }
    }
}
void Matrix::subtract(double b){
    this->checkMatrix();
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = this->data[y][x];
            this->data[y][x] = val-b;
        }
    }
}
Matrix Matrix::subtract(Matrix &a,Matrix &b){
    if((a.getNumRows() != b.getNumRows())||(a.getNumCols() != b.getNumCols())){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        Matrix result(a.getNumRows(),a.getNumCols());
        for(int y=0;y<a.getNumRows();y++){
            for(int x=0;x<a.getNumCols();x++){
                result.setData(y, x, (a.data[y][x] - b.data[y][x]));
            }
        }
        return result;
    }
}


void Matrix::hadamardProduct(Matrix b){
    //std::cout<<"STATUS: Preforming hadamard product"<<std::endl;
    this->checkMatrix();
    if(this->getNumRows()==b.getNumRows() && this->getNumCols()==b.getNumCols()){
        for(int y=0;y<getNumRows();y++){
            for(int x=0;x<getNumCols();x++){
                double val = this->data[y][x];
                this->data[y][x] = val*b.data[y][x];
            }
        }
    }else{
        std::cout<<"ERROR: Size of matrices Must match."<<std::endl;
        return;
    }
}

void Matrix::scalarProduct(double b){
    //std::cout<<"STATUS: Preforming scalar product"<<std::endl;
    this->checkMatrix();
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = this->data[y][x];
            this->data[y][x] = val*b;
        }
    }
}

void Matrix::transpose(){
    std::vector<std::vector<double>> newMatrix;
    unsigned long int numCols = this->getNumCols();
    unsigned long int numRows = this->getNumRows();
    if(numRows != numCols){
        unsigned long int tmp = numCols;
        numCols = numRows;
        numRows = tmp;
    }
    for(int y=0;y<numRows;y++){
        std::vector<double> tmp;
        for(int x=0;x<numCols;x++){
            tmp.push_back(this->data[x][y]);
        }
        newMatrix.push_back(tmp);
    }
    this->data.clear();
    for(int y=0;y<numRows;y++){
        std::vector<double> temp;
        for(int x=0;x<numCols;x++){
            temp.push_back(newMatrix[y][x]);
        }
        this->data.push_back(temp);
    }
}

void Matrix::checkMatrix(){
    if(this->data.size()<0){
        std::cout<<"ERROR: No matrix exists."<<std::endl;
        exit(1);
    }
}

Matrix Matrix::operator +(Matrix &obj){
    Matrix result;
    if((this->getNumRows() != obj.getNumRows())||(this->getNumCols() != obj.getNumCols())){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        for(int y=0;y<this->getNumRows();y++){
            std::vector<double> temp;
            for(int x=0;x<this->getNumCols();x++){
                double val = this->data[y][x];
                temp.push_back(val + obj.data[y][x]);
            }
            result.data.push_back(temp);
        }
    }
    return result;
}

Matrix Matrix::operator -(Matrix &obj){
    Matrix result;
    if((this->getNumRows() != obj.getNumRows())||(this->getNumCols() != obj.getNumCols())){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        for(int y=0;y<this->getNumRows();y++){
            std::vector<double> temp;
            for(int x=0;x<this->getNumCols();x++){
                double val = this->data[y][x];
                temp.push_back(val - obj.data[y][x]);
            }
            result.data.push_back(temp);
        }
    }
    return result;
}

Matrix Matrix::operator *(Matrix &obj){ //Cross product
    //std::cout<<"STATUS: Preforming cross product"<<std::endl;
    
    if(this->getNumCols() == obj.getNumRows()){
        Matrix result(this->getNumRows(),obj.getNumCols());
        for(int y=0;y<result.getNumRows();y++){
            for(int x=0;x<result.getNumCols();x++){
                double sum = 0;
                for(int z=0;z<this->getNumCols();z++){
                    sum += this->getData(y,z)*obj.getData(z,x);
                }
                result.setData(y,x,sum);
            }
        }
        return result;
    }else{
        std::cout<<"ERROR: Columns of A must match rows of B."<<std::endl;
        exit(1);
    }
}
Matrix Matrix::operator ->*(Matrix &obj){ //Hadamard product
    //std::cout<<"STATUS: Preforming hadamard product"<<std::endl;
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

Matrix Matrix::operator *(double &obj){ //Scalar product
    Matrix result(this->getNumRows(),this->getNumCols());
    //std::cout<<"STATUS: Preforming scalar product"<<std::endl;
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            double val = this->data[y][x];
            result.data[y][x] = val*obj;
        }
    }
    return result;
}


void Matrix::roundToBool(){
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            if(this->data[y][x] >= 0.5){
                this->data[y][x] = 1;
            }else{
                this->data[y][x] = 0;
            }
        }
    }
}

void Matrix::roundToThousandths(){
    for(int y=0;y<getNumRows();y++){
        for(int x=0;x<getNumCols();x++){
            this->data[y][x] = floor(this->data[y][x] * 1000.0 + 0.5)/1000;
        }
    }
}
