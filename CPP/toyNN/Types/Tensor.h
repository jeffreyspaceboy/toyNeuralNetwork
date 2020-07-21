//
//  Tensor.h
//  toyNN
//
//  Created by Jeffrey Fisher on 6/2/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//


#ifndef Tensor_h
#define Tensor_h

#include <iostream>
#include <vector>

#include "Cell.h"
#include "Shape.h"
#include "Activation.h"

class Tensor{
    public:
        //---Constructors---//
        Tensor(void);
        Tensor(std::vector<float> data, Shape shape);
        Tensor(Shape shape, bool randomize = false);
    
        //---Copy Constructors---//
        Tensor(const Tensor &obj);
        //---Destructors---//
        ~Tensor(void);
    
        //---Set---//
        void set_shape(Shape shape);
        void set_data(std::vector<float> data, Shape shape);
        void set_data(float  data, Shape shape);
        void set_cell(float  data, Cell cell);
        void set_cell(float  data, unsigned int cell);

        //---Get---//
        Shape get_shape(void);
        std::vector<float> get_data(void);
        float get_cell(unsigned int cell);
        float get_cell(Cell cell);
        
        //---Operations---//
        void map(float func(float val, Cell cell));
        Tensor *map(Tensor *a, float func(float val, Cell cell));
    
        //TODO: Math using map (will be more efficient)
    
        void add(Tensor &obj);
        void add(float obj);
        void subtract(Tensor &obj);
        void subtract(float obj);
        void hadamard_product(Tensor &obj);
        void scalar_product(float obj);

        Tensor operator +(Tensor &obj);
        Tensor operator +(float obj);
        Tensor operator -(Tensor &obj);
        Tensor operator -(float obj);
        Tensor operator *(Tensor &obj);
        Tensor operator ->*(Tensor &obj);
        Tensor operator *(float obj);
    
        Tensor operator ~(void);
        Tensor transposed(void);
    
        float random(int lowerBound, int upperBound, int decimal_precision = 1000);
        void randomize(int lowerBound, int upperBound, int decimal_precision = 1000);
        void round_to(float val);

        //---Activation Functions---//
        void sigmoid(void);
        void dSigmoid(void);

        //---Checking---//
        bool check_matrix(void);
        bool check_shape(Shape shape);
    
        //---Other---//
        void print(void);
    private:
        std::vector<float> data;
        Shape shape;
};
#endif /* Tensor_h */