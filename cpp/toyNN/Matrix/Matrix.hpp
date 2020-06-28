////
////  Matrix.hpp
////  toyNN
////
////  Created by Jeffrey Fisher on 2/10/20.
////  Copyright © 2020 Jeffrey Fisher. All rights reserved.
////
//
//#ifndef Matrix_hpp
//#define Matrix_hpp
//
//#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <math.h>
//
//class Matrix{
//    private:
//        unsigned long int num_rows;
//        unsigned long int num_cols;
//        double *data = NULL;
//    public:
//        //---Constructors---//
//        Matrix(unsigned long int rows, unsigned long int cols); //Size Based
//        Matrix(std::vector<std::vector<double>> newData); //Vector
//        Matrix(); //Standard
//        //---Copy Constructors---//
//        Matrix(const Matrix &obj);
//        //---Destructors---//
//        ~Matrix();
//
//        //---Get---//
//        unsigned long int getNumRows();
//        unsigned long int getNumCols();
//        std::vector<std::vector<double>> getData();
//        double getData(int y, int x);
//
//        //---Set---//
//        void setData(int y, int x, double newData);
//
//        //---Math Operations---//
//        void map(double func(double val,int y, int x));
//        Matrix map(Matrix a, double func(double val,int y, int x));
//
//        Matrix operator +(Matrix &obj);
//        Matrix operator -(Matrix &obj);
//        Matrix operator *(Matrix &obj);
//        Matrix operator ->*(Matrix &obj);
//        Matrix operator *(double &obj);
//        Matrix transposed();
//        void randomize(int lowerBound, int upperBound);
//        void roundTo(double val);
//
//        //---Activation Functions---//
//        void sigmoid();
//        void dSigmoid();
//
//        //---Other---//
//        void checkMatrix();
//        void print();
//};
//#endif /* Matrix_hpp */
