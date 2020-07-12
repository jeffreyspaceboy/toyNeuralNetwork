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

#include "Shape.hpp"
#include "Cell.hpp"
#include "Activation.hpp"

class Matrix{
    public:
        //---Constructors---//
        Matrix();
        Matrix(float *data, Shape shape);
        Matrix(Shape shape, bool randomize = false);
    
        Matrix(float *data, unsigned int x_size, unsigned int y_size);
        Matrix(unsigned int x_size, unsigned int y_size);
        //---Copy Constructors---//
        Matrix(const Matrix &obj);
        //---Destructors---//
        ~Matrix();

        //---Get---//
        Shape get_shape();
        float *get_data();
        float get_cell(Cell cell);
        //TODO: ADD GET DATA TRANSPOSED? Maybe just get cell transposed

        //---Set---//
        void set_shape(Shape shape);
        void set_data(float *data, Shape shape);
        void set_data(float  data, Shape shape);
        void set_cell(float  data, Cell cell);
        void set_useful_data(float *data, Shape shape);
        
        //---Operations---//
        void map(float func(float val, Cell cell));
        Matrix *map(Matrix *a, float func(float val, Cell cell));
    
        //TODO: Math using map (will be more efficient)
    
        void add(Matrix &obj);
        void add(float obj);
        void subtract(Matrix &obj);
        void subtract(float obj);
        void hadamard_product(Matrix &obj);
        void scalar_product(float obj);

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
        bool check_shape(Shape shape);
    
        //---Other---//
        void print();
    
    private:
        float *data = NULL;
        Shape shape;
};
#endif /* Matrix_hpp */
