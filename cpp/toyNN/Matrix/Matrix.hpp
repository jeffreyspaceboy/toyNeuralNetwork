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
//#include <sstream>
//#include <fstream>
#include <math.h>

class Matrix{
    private:
        std::string name = "MatrixName";
        unsigned int data_size = 0; //Total
        unsigned int data_shape[2] = {0,0}; //[Rows,Cols] or [y,x]
        double *data = NULL;
    public:
        //---Constructors---//
        Matrix(); //Standard
        Matrix(double *data, unsigned int data_shape[2]);
        Matrix(unsigned int data_shape[2], bool randomize = false);
        //---Copy Constructors---//
        Matrix(const Matrix &obj);
        //---Destructors---//
        ~Matrix();

        //---Get---//
        unsigned int *get_data_shape();
        unsigned int get_data_size();
        double *get_data();
        double get_data(unsigned int cell[2]);
        //POTENTIAL TODO: ADD GET DATA TRANSPOSED
        

        //---Set---//
        void set_shape(unsigned int data_shape[2]);
        void set_data(double *data, unsigned int data_shape[2]);
        void set_data(double data, unsigned int cell[2]);

        //---Operations---//
        void map(double func(double val, unsigned int cell[2]));
        Matrix *map(Matrix *a, double func(double val, unsigned int cell[2]));

        Matrix operator +(Matrix &obj);
        Matrix operator -(Matrix &obj);
        Matrix operator *(Matrix &obj);
        Matrix operator ->*(Matrix &obj);
        Matrix operator *(double obj);
    
        Matrix transposed();
    
        void randomize(int lowerBound, int upperBound);
        void round_to(double val);

        //---Activation Functions---//
        void sigmoid();
        void dSigmoid();

        //---Other---//
        bool checkMatrix();
        void print();
};
#endif /* Matrix_hpp */
