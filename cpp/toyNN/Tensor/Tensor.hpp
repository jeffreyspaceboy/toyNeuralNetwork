//
//  Tensor.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 6/2/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Tensor_hpp
#define Tensor_hpp

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>

class Tensor{
    private:
        std::vector<std::vector<double>> data; //2D Vector to store matrix data
    public:
        //---Constructors---//
        Tensor(unsigned long int rows, unsigned long int cols); //Size Based
        Tensor(std::vector<std::vector<double>> newData); //Vector
        Tensor(); //Standard
        //---Copy Constructors---//
        Tensor(const Tensor &obj);
        //---Destructors---//
        ~Tensor();
    
        //---Get---//
        //unsigned long int getNumRows();
        //unsigned long int getNumCols();
        //std::vector<std::vector<double>> getData();
        //double getData(int y, int x);
    
        //---Set---//
        //void setData(int y, int x, double newData);
    
        //---Math Operations---//
        //void map(double func(double val,int y, int x));
        //Matrix map(Matrix a, double func(double val,int y, int x));
    
        //Matrix operator +(Matrix &obj);
        //Matrix operator -(Matrix &obj);
        //Matrix operator *(Matrix &obj);
        //Matrix operator ->*(Matrix &obj);
        //Matrix operator *(double &obj);
        //Matrix transposed();
        //void randomize(int lowerBound, int upperBound);
        //void roundTo(double val);
    
        //---Activation Functions---//
        //void sigmoid();
        //void dSigmoid();
        
        //---Other---//
        //void checkMatrix();
        //void print();
};
#endif /* Tensor_hpp */
