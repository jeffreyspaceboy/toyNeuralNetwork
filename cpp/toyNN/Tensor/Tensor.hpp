////
////  Tensor.hpp
////  toyNN
////
////  Created by Jeffrey Fisher on 6/2/20.
////  Copyright © 2020 Jeffrey Fisher. All rights reserved.
////
//
//
//
//#ifndef NULL
//#define NULL 0
//#endif
//
//
//
//#ifndef Tensor_hpp
//#define Tensor_hpp
//
//#include <iostream>
////#include <sstream>
////#include <fstream>
////#include <vector>
//#include <math.h>
//
//#include "Matrix.hpp"
//
//class Tensor{
//    private:
//        std::string name = "TensorName";
//        unsigned int data_size = 0; //Total
//        unsigned int data_shape[3] = {0,0,0}; //[Layers,Rows,Cols] or (z,y,x)
//        double *data = NULL;
//    public:
//        //---Constructors---//
//        Tensor(); //Standard
//        Tensor(double *data, unsigned int z_size, unsigned int y_size, unsigned int x_size); //Size Based Pass Pointer
//        Tensor(unsigned int z_size, unsigned int y_size, unsigned int x_size, bool randomize = false);
//        //---Copy Constructors---//
//        Tensor(const Tensor &obj);
//        //---Destructors---//
//        ~Tensor();
//
//        //---Get---//
//        std::string get_name();
//        unsigned int get_z_size();
//        unsigned int get_y_size();
//        unsigned int get_x_size();
//        unsigned int get_total_size();
//        double *get_data();
//
//        //---Set---//
//        void zero();
//        void set_name(std::string new_name);
//        void set_element(double val, unsigned int z, unsigned int y, unsigned int x);
//        void set_data(double *input_data, unsigned int z_size, unsigned int y_size, unsigned int x_size);
//        void copy_data(const Tensor &sampleTensor);
//
//        //---Math Operations---//
//        void map(double func(double val, unsigned int z, unsigned int y, unsigned int x));
//        Tensor map(const Tensor &obj, double func(double val, unsigned int z, unsigned int y, unsigned int x));
//
//        Tensor operator +(const Tensor &obj); //Element-Wise Addition
//        Tensor operator -(const Tensor &obj); //Element-Wise Subtraction
//        Tensor operator *(const Tensor &obj); //Element-Wise Multiplication
//        Tensor operator *(const double &obj); //Element-Wise Multiplication with Scalar
//        Tensor operator ->*(const Tensor &obj); //Matrix Multiplication
//
//        Tensor transposed();
//        void randomize(int lowerBound, int upperBound);
//        void roundTo(double val);
//
//        //---Activation Functions---//
//        void sigmoid();
//        void dSigmoid();
//
//        //---Other---//
//        //void checkMatrix();
//        void print();
//};
//#endif /* Tensor_hpp */
