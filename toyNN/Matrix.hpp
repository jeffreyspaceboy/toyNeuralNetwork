//
//  Matrix.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

#define maxDataSize 128

class Matrix{
    private:
        unsigned long int numRows;
        unsigned long int numCols;
        std::vector<std::vector<double>> data;
    public:
        Matrix();
        Matrix(unsigned long int rows, unsigned long int cols);
        Matrix(std::vector<std::vector<double>> newData);
        Matrix(const Matrix &obj);
        ~Matrix();
    
        void print();
    
        void fillFrom(std::vector<std::vector<double>> &vect);
        void fillFrom(double array[maxDataSize][maxDataSize]);
        void randomize(int lowerBound, int upperBound);
    
        unsigned long int getNumRows();
        unsigned long int getNumCols();
        double getData(int y, int x);
        std::vector<std::vector<double>> getData();
        void setData(int y, int x, double newData);
    
        void map(double func(double val,int y, int x));
        Matrix map(Matrix &a, double func(double val,int y, int x));
        void sigmoid();
        void dSigmoid();
    
        void add(Matrix b);
        void add(double b);
        void subtract(Matrix b);
        void subtract(double b);
        Matrix subtract(Matrix &a, Matrix &b);
        void hadamardProduct(Matrix b);
        void scalarProduct(double b);
        Matrix crossProduct(Matrix &a, Matrix &b);
    
        void transpose();
        void checkMatrix();
    
        Matrix operator +(Matrix const &obj);
        Matrix operator -(Matrix const &obj);
        Matrix operator *(Matrix &obj);
        Matrix operator ->*(Matrix &obj);
        Matrix operator *(double &obj);
        
};


#endif /* Matrix_hpp */
