//
//  Layer.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Layer_hpp
#define Layer_hpp

#include "Tensor.hpp"

class Layer{
    private:
        //sig(W*in + b)=out

    public:
        Tensor inputs;
        Tensor inputsT;
        Tensor weights;
        Tensor weightsT;
        Tensor biases;
        Tensor outputs;

        Tensor outputError;
        Tensor gradient;
        Tensor weightsDelta;
        Tensor inputError;

        Layer();
        Layer(int numStartNodes, int numEndNodes);
        Layer(const Layer &obj);
        ~Layer();
        void randomize(int lowerBound, int upperBound);
        void setInputs(Tensor data, bool doTranspose);

        Tensor solveForOutputs();
        Tensor getInputs();
        Tensor getWeights();
        Tensor getBiases();

        void setWeightsDelta(Tensor &obj);
        void setWeightsTransposed();
        void setInputsTransposed();

        void roundTo(double val);
};

#endif /* Layer_hpp */
