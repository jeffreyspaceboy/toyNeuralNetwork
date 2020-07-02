//
//  Matrix.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//


#define Matrix_hpp
#ifdef Matrix_hpp


#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <math.h>

class Matrix{
    private:
        unsigned int y_size; //Rows
        unsigned int x_size; //Cols
        unsigned int data_size; //Total
        double *data = NULL;
    public:
        //---Constructors---//
        Matrix(double *data, unsigned int y_size, unsigned int x_size, bool randomize = false); //Size Based
        Matrix(unsigned int y_size, unsigned int x_size, bool randomize = false); //Size Based
        Matrix(); //Standard
        //---Copy Constructors---//
        Matrix(const Matrix &obj);
        //---Destructors---//
        ~Matrix();

        //---Get---//
        unsigned int get_y_size();
        unsigned int get_x_size();
        unsigned int get_data_size();
        double *get_data();
        double get_data(unsigned int y, unsigned int x);

        //---Set---//
        void set_size(unsigned int y_size, unsigned int x_size);
        void set_data(double *data, unsigned int y_size, unsigned int x_size);

        //---Operations---//
        void map(double func(double val, unsigned int y, unsigned int x));
        Matrix *map(Matrix *a, double func(double val, unsigned int y, unsigned int x));

        Matrix operator +(Matrix &obj);
        Matrix operator -(Matrix &obj);
        Matrix operator *(Matrix &obj);
        Matrix operator ->*(Matrix &obj);
        Matrix operator *(double &obj);
    
        void transpose();
        Matrix transposed();
    
        void randomize(unsigned int lowerBound, unsigned int upperBound);
        void roundTo(double val);

        //---Activation Functions---//
        void sigmoid();
        void dSigmoid();

        //---Other---//
        void checkMatrix();
        void print();
};
#endif /* Matrix_hpp */
