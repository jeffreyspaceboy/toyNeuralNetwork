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
#include <math.h>

class Matrix{
    private:
        unsigned int y_size = 0; //Rows
        unsigned int x_size = 0; //Cols
        unsigned int data_size = 0; //Total
        double *data = NULL;
    public:
        //---Constructors---//
        Matrix(); //Standard
        Matrix(double *data, unsigned int y_size, unsigned int x_size);
        Matrix(unsigned int y_size, unsigned int x_size, bool randomize = false);
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
        //POTENTIAL TODO: ADD GET DATA TRANSPOSED
        

        //---Set---//
        void set_size(unsigned int y_size, unsigned int x_size);
        void set_data(double *data, unsigned int y_size, unsigned int x_size);
        void set_data(double data, unsigned int y, unsigned int x);

        //---Operations---//
        void map(double func(double val, unsigned int y, unsigned int x));
        Matrix *map(Matrix *a, double func(double val, unsigned int y, unsigned int x));

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
