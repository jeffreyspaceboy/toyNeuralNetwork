//
//  Tensor.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 6/2/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//


#ifndef Tensor_hpp
#define Tensor_hpp

#include "Matrix.hpp"

class Tensor{
    public:
        //---Constructors---//
        Tensor();
        Tensor(float *data, unsigned int shape[3]);
        Tensor(unsigned int data_shape[3], bool randomize = false);
    
        Tensor(float *data, unsigned int z_size, unsigned int y_size, unsigned int x_size);
        Tensor(unsigned int z_size, unsigned int y_size, unsigned int x_size);
        //---Copy Constructors---//
        Tensor(const Tensor &obj);
        //---Destructors---//
        ~Tensor();

        //---Get---//
        unsigned int *get_shape();
        unsigned int get_size();
        float *get_data();
        float get_cell(unsigned int cell[3]);

        //---Set---//
        void set_shape(unsigned int shape[3]);
        void set_data(float *data, unsigned int shape[3]);
        void set_data(float  data, unsigned int shape[3]);
        void set_cell(float  data, unsigned int  cell[3]);
        void set_useful_data(float *data, unsigned int shape[3]);
        
        //---Operations---//
        void map(float func(float val, unsigned int cell[3]));
        Tensor *map(Tensor *a, float func(float val, unsigned int cell[3]));

        Tensor operator +(Tensor &obj);
        Tensor operator -(Tensor &obj);
        Tensor operator *(Tensor &obj);
        Tensor operator ->*(Tensor &obj);
        Tensor operator *(float obj);
    
        Tensor operator ~();
        Tensor transposed();
    
        float random(int lowerBound, int upperBound, int decimal_precision = 1000);
        void randomize(int lowerBound, int upperBound, int decimal_precision = 1000);
        void round_to(float val);

        //---Activation Functions---//
        void sigmoid();
        void dSigmoid();

        //---Checking---//
        bool check_matrix();
        bool check_shape(unsigned int shape[3]);
    
        //---Other---//
        void print();
    
    private:
        float *data = NULL;
        unsigned int shape[3] = {0,0,0};
        unsigned int size = 0;
};
#endif /* Tensor_hpp */
