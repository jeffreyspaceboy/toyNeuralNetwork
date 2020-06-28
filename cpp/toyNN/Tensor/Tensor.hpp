//
//  Tensor.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 6/2/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//



#ifndef NULL
#define NULL 0
#endif



#ifndef Tensor_hpp
#define Tensor_hpp

#include <iostream>
//#include <sstream>
//#include <fstream>
//#include <vector>
//#include <math.h>

class Tensor{
    private:
        std::string name = "TensorName";
        unsigned int x_size = 0;
        unsigned int y_size = 0;
        unsigned int z_size = 0;
        double ***data = NULL;
    public:
        //---Constructors---//
        Tensor(); //Standard
        Tensor(double ***input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size, std::string name = "TensorName"); //Size Based Pass Pointer
        Tensor(double *input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size, std::string name = "TensorName");
        Tensor(unsigned int x_size, unsigned int y_size, unsigned int z_size);
        //---Copy Constructors---//
        Tensor(const Tensor &obj);
        //---Destructors---//
        ~Tensor();

        //---Get---//
        std::string get_name();
        unsigned int get_x_size();
        unsigned int get_y_size();
        unsigned int get_z_size();
        double ***get_data();

        //---Set---//
        void zero();
        void set_name(std::string new_name);
        void set_element(double val, unsigned int x, unsigned int y, unsigned int z);
        void set_data(double ***input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size);
        void set_data(double *input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size);
        void copy_data(const Tensor &sampleTensor);
        
        //---Math Operations---//
        void map(double func(double val, unsigned int x, unsigned int y, unsigned int z));
        Tensor map(const Tensor &obj, double func(double val, unsigned int x, unsigned int y, unsigned int z));

        Tensor operator +(const Tensor &obj); //Element-Wise Addition
        Tensor operator -(const Tensor &obj); //Element-Wise Subtraction
        Tensor operator *(const Tensor &obj); //Element-Wise Multiplication
        Tensor operator ->*(const Tensor &obj); //Matrix Multiplication
        //Tensor operator ->*(const Tensor &obj);
        //Tensor operator *(const double &obj);
        //Matrix transposed();
        //void randomize(int lowerBound, int upperBound);
        //void roundTo(double val);

        //---Activation Functions---//
        //void sigmoid();
        //void dSigmoid();

        //---Other---//
        //void checkMatrix();
        void print();
};
#endif /* Tensor_hpp */
