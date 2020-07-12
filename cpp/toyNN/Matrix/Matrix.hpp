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
#include <math.h>

class Matrix{
    public:
        //---Constructors---//
        Matrix();
        Matrix(float *data, unsigned int shape[2]);
        Matrix(unsigned int data_shape[2], bool randomize = false);
    
        Matrix(float *data, unsigned int y_size, unsigned int x_size);
        Matrix(unsigned int y_size, unsigned int x_size);
        //---Copy Constructors---//
        Matrix(const Matrix &obj);
        //---Destructors---//
        ~Matrix();

        //---Get---//
        unsigned int *get_shape();
        unsigned int get_size();
        float *get_data();
        float get_cell(unsigned int cell[2]);
        //TODO: ADD GET DATA TRANSPOSED? Maybe just get cell transposed

        //---Set---//
        void set_shape(unsigned int shape[2]);
        void set_data(float *data, unsigned int shape[2]);
        void set_data(float  data, unsigned int shape[2]);
        void set_cell(float  data, unsigned int  cell[2]);
        void set_useful_data(float *data, unsigned int shape[2]);
        
        //---Operations---//
        void map(float func(float val, unsigned int cell[2]));
        Matrix *map(Matrix *a, float func(float val, unsigned int cell[2]));
    
        //TODO: Math using map (will be more efficient)

        Matrix operator +(Matrix &obj);
        Matrix operator -(Matrix &obj);
        Matrix operator *(Matrix &obj);
        Matrix operator ->*(Matrix &obj);
        Matrix operator *(float obj);
    
        Matrix operator ~();
        Matrix transposed();
    
        float random(int lowerBound, int upperBound, int decimal_precision = 1000);
        void randomize(int lowerBound, int upperBound, int decimal_precision = 1000);
        void round_to(float val);

        //---Activation Functions---//
        void sigmoid();
        void dSigmoid();

        //---Checking---//
        bool check_matrix();
        bool check_shape(unsigned int shape[2]);
    
        //---Other---//
        void print();
    
    private:
        float *data = NULL;
        unsigned int shape[2] = {0,0};
        unsigned int size = 0;
};
#endif /* Matrix_hpp */
