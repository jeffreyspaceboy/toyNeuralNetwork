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
        
    public:
        Matrix inputs;
        Matrix inputsT;
        Matrix weights;
        Matrix weightsT;
        Matrix biases;
        Matrix outputs;
    
        Matrix outputError;
        Matrix gradient;
        Matrix weightsDelta;
        Matrix inputError;
    
        
    
        Layer();
        Layer(int numStartNodes, int numEndNodes);
        Layer(const Layer &obj);
        ~Layer();
        void randomize(int lowerBound, int upperBound);
        void setInputs(Matrix data, bool doTranspose);
    
        Matrix solveForOutputs();
        Matrix getInputs();
        Matrix getWeights();
        Matrix getBiases();
    
        void setWeightsDelta(Matrix &obj);
        void setWeightsTransposed();
        void setInputsTransposed();
    
        void roundToThousandths();
};

#endif /* Layer_hpp */
