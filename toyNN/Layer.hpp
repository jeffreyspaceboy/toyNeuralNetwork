//
//  Layer.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Layer_hpp
#define Layer_hpp

#include <stdio.h>
#include "Matrix.hpp"

class Layer{
    private:
        //sig(W*in + b)=out
        Matrix inputs;
        Matrix weights;
        Matrix biases;
        Matrix outputs;
    public:
        Layer();
        Layer(int numStartNodes, int numEndNodes);
        Layer(const Layer &obj);
        ~Layer();
        void randomize(int lowerBound, int upperBound);
        void setInputs(Matrix data, bool doTranspose);
        Matrix getOutputs();
        Matrix getInputs();
        Matrix getWeights();
        Matrix getBiases();
};

#endif /* Layer_hpp */
