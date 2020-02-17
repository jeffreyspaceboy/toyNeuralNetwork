//
//  Matrix.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Matrix.hpp"

Matrix::Matrix(){
    //Do Nothing
}

Matrix::Matrix(unsigned long int rows, unsigned long int cols){
    this->numRows = rows;
    this->numCols = cols;
    std::cout<<"STATUS: Generating a Clean ["<<this->numRows<<","<<this->numCols<<"] Matrix"<<std::endl;
    for(int y=0;y<(this->numRows);y++){
        std::vector<double> temp;
        for(int x=0;x<(this->numCols);x++){
            temp.push_back(0);
        }
        this->data.push_back(temp);
    }
}


Matrix::Matrix(std::vector<std::vector<double>> newData){
    this->data = newData;
    this->numRows = this->getNumRows();
    this->numCols = this->getNumCols();
    std::cout<<"STATUS: Generating a ["<<this->numRows<<","<<this->numCols<<"] Matrix"<<std::endl;
}


Matrix::Matrix(const Matrix &obj){
    //std::cout<<"STATUS: Copying Matrix"<<std::endl;
    this->numRows = obj.numRows;
    this->numCols = obj.numCols;
    this->data = obj.data;
}

Matrix::~Matrix(void){
    //std::cout<<"STATUS: Clearing Matrix"<<std::endl;
}

//Fills Data vector with vector data
void Matrix::fillFrom(std::vector<std::vector<double>> &vect){
    for(int y=0;y<(this->numRows);y++){
        for(int x=0;x<(this->numCols);x++){
            this->data[y][x] = vect[y][x];
        }
    }
}

void Matrix::fillFrom(double array[maxDataSize][maxDataSize]){
    for(int y=0;y<maxDataSize;y++){
        for(int x=0;x<maxDataSize;x++){
            this->data[y][x] = array[y][x];
        }
    }
}

void Matrix::randomize(int lowerBound, int upperBound){
    for(int y=0;y<(this->numRows);y++){
        for(int x=0;x<(this->numCols);x++){
            this->data[y][x] = (rand() % (upperBound-lowerBound+1) + lowerBound);
        }
    }
}


unsigned long int Matrix::getNumRows(){
    return this->data.size();
}

unsigned long int Matrix::getNumCols(){
    return this->data[0].size();
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
    std::cout<<"-------------------v"<<std::endl;
    this->checkMatrix();
    for(int y=0;y<numRows;y++){
        std::cout<<"[";
        for(int x=0;x<numCols-1;x++){
            std::cout<<this->data[y][x]<<",";
        }
        std::cout<<this->data[y][numCols-1]<<"]"<<std::endl;
    }
    std::cout<<"-------------------^"<<std::endl;
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
    for(int y=0;y<numRows;y++){
        for(int x=0;x<numCols;x++){
            double val = this->data[y][x];
            this->data[y][x] = (*func)(val,y,x);
        }
    }
}

Matrix Matrix::map(Matrix &a, double (*func)(double val,int y,int x)){
    Matrix result;
    result = a;
    for(int y=0;y<numRows;y++){
        for(int x=0;x<numCols;x++){
            double val = result.data[y][x];
            result.data[y][x] = (*func)(val,y,x);
        }
    }
    return result;
}

void Matrix::sigmoid(){
    map(singleSigmoid);
}
void Matrix::dSigmoid(){
    map(singleDSigmoid);
}

void Matrix::add(Matrix b){
    this->checkMatrix();
    //this->print();
    //b.print();
    if((this->numRows != b.numRows)||(this->numCols != b.numCols)){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        for(int y=0;y<numRows;y++){
            for(int x=0;x<numCols;x++){
                double val = this->data[y][x];
                this->data[y][x] = val + b.data[y][x];
            }
        }
    }
}

void Matrix::add(double b){
    this->checkMatrix();
    for(int y=0;y<numRows;y++){
        for(int x=0;x<numCols;x++){
            double val = this->data[y][x];
            this->data[y][x] = val+b;
        }
    }
}

void Matrix::subtract(Matrix b){
    this->checkMatrix();
    if((this->numRows != b.numRows)||(this->numCols != b.numCols)){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        return;
    }else{
        for(int y=0;y<numRows;y++){
            for(int x=0;x<numCols;x++){
                double val = this->data[y][x];
                this->data[y][x] = val - b.data[y][x];
            }
        }
    }
}
void Matrix::subtract(double b){
    this->checkMatrix();
    for(int y=0;y<numRows;y++){
        for(int x=0;x<numCols;x++){
            double val = this->data[y][x];
            this->data[y][x] = val-b;
        }
    }
}
Matrix Matrix::subtract(Matrix &a,Matrix &b){
    if((a.numRows != b.numRows)||(a.numCols != b.numCols)){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        Matrix result(a.getNumRows(),a.getNumCols());
        for(int y=0;y<a.numRows;y++){
            for(int x=0;x<a.numCols;x++){
                result.setData(y, x, (a.data[y][x] - b.data[y][x]));
            }
        }
        return result;
    }
}


void Matrix::hadamardProduct(Matrix b){
    std::cout<<"STATUS: Preforming hadamard product"<<std::endl;
    this->checkMatrix();
    if(this->numRows==b.getNumRows()||this->numCols==b.getNumCols()){
        for(int y=0;y<numRows;y++){
            for(int x=0;x<numCols;x++){
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
    std::cout<<"STATUS: Preforming scalar product"<<std::endl;
    this->checkMatrix();
    for(int y=0;y<numRows;y++){
        for(int x=0;x<numCols;x++){
            double val = this->data[y][x];
            this->data[y][x] = val*b;
        }
    }
}

Matrix Matrix::crossProduct(Matrix &a, Matrix &b){
    std::cout<<"STATUS: Preforming cross product"<<std::endl;
    //a.print();
    //b.print();
    if(a.getNumCols() == b.getNumRows()){
        Matrix result(a.getNumRows(),b.getNumCols());
        for(int y=0;y<result.getNumRows();y++){
            for(int x=0;x<result.getNumCols();x++){
                double sum = 0;
                for(int z=0;z<a.getNumCols();z++){
                    sum += a.getData(y,z)*b.getData(z,x);
                }
                result.setData(y,x,sum);
            }
        }
        //result.print();
        return result;
    }else{
        std::cout<<"ERROR: Columns of A must match rows of B."<<std::endl;
        exit(1);
    }
}

void Matrix::transpose(){
    this->checkMatrix();
    std::vector<std::vector<double>> newMatrix;
    if(this->numRows != this->numCols){
        unsigned long int tmp = this->numCols;
        this->numCols = this->numRows;
        this->numRows = tmp;
    }
    for(int y=0;y<numRows;y++){
        std::vector<double> tmp;
        for(int x=0;x<numCols;x++){
            tmp.push_back(this->data[x][y]);
        }
        newMatrix.push_back(tmp);
    }
    this->data.clear();
    for(int y=0;y<this->numRows;y++){
        std::vector<double> temp;
        for(int x=0;x<this->numCols;x++){
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

Matrix Matrix::operator +(Matrix const &obj){
    Matrix result;
    if((this->numRows != obj.numRows)||(this->numCols != obj.numCols)){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        for(int y=0;y<this->numRows;y++){
            std::vector<double> temp;
            for(int x=0;x<this->numCols;x++){
                double val = this->data[y][x];
                temp.push_back(val + obj.data[y][x]);
            }
            result.data.push_back(temp);
        }
    }
    return result;
}

Matrix Matrix::operator -(Matrix const &obj){
    Matrix result;
    if((this->numRows != obj.numRows)||(this->numCols != obj.numCols)){
        std::cout<<"ERROR: Columns and Rows must match."<<std::endl;
        exit(1);
    }else{
        for(int y=0;y<this->numRows;y++){
            std::vector<double> temp;
            for(int x=0;x<this->numCols;x++){
                double val = this->data[y][x];
                temp.push_back(val - obj.data[y][x]);
            }
            result.data.push_back(temp);
        }
    }
    return result;
}

Matrix Matrix::operator *(Matrix const &obj){
    Matrix result;
    
    return result;
}
Matrix Matrix::operator ->*(Matrix const &obj){
    Matrix result;
    return result;
}
Matrix Matrix::operator *(double &obj){
    Matrix result;
    return result;
}
