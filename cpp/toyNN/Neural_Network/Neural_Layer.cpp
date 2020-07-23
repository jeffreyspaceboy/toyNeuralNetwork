//
//  Neural_Layer.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Neural_Layer.h"


//---Constructors---//
Neural_Layer::Neural_Layer(){}

Neural_Layer::Neural_Layer(const unsigned int numStartNodes, const unsigned int numEndNodes){
    this->inputs = Tensor(Shape(1,numStartNodes));
    this->weights = Tensor(Shape(numStartNodes,numEndNodes), true);
    this->biases = Tensor(Shape(1,numEndNodes), true);
    this->outputs = Tensor(Shape(1,numEndNodes));

    //this->randomize(-1,1);

    this->inputsT = ~(this->inputs);
    this->weightsT = ~(this->weights);
    
    this->outputError = Tensor(Shape(1,numEndNodes));
    this->gradient = Tensor(Shape(1,numEndNodes));
    this->weightsDelta = Tensor(Shape(numStartNodes,numEndNodes));
    this->inputError = Tensor(Shape(1,numStartNodes));
}


//---Copy Constructors---//
Neural_Layer::Neural_Layer(const Neural_Layer &obj){
    //std::cout<<"STATUS: Copying Neural_Layer"<<std::endl;
    this->inputs = obj.inputs;
    this->weights = obj.weights;
    this->biases = obj.biases;
    this->outputs = obj.outputs;

    this->inputsT = obj.inputsT;
    this->weightsT = obj.weightsT;

    this->outputError = obj.outputError;
    this->gradient = obj.gradient;
    this->weightsDelta = obj.weightsDelta;
    this->inputError = obj.inputError;
}

//---Destructors---//
Neural_Layer::~Neural_Layer(void){}


//---Get---//
Tensor Neural_Layer::get_inputs(void){return this->inputs;}
Tensor Neural_Layer::get_weights(void){return this->weights;}
Tensor Neural_Layer::get_biases(void){return this->biases;}


//---Set---//
void Neural_Layer::set_inputs(Tensor data, bool doTranspose){
    this->inputs = data;
    if(doTranspose){
        this->inputs = this->inputs.transposed();
    }
}

void Neural_Layer::set_weights_delta(Tensor &obj){this->weightsDelta = obj;}


//---Operations---//
Tensor Neural_Layer::solve_outputs(void){
    this->outputs = (this->weights * this->inputs) + this->biases;
    this->outputs.sigmoid();
    this->outputs.round_to(10000.0);
    return this->outputs;
}

void Neural_Layer::round_to(float val){
    this->weights.round_to(val);
    this->biases.round_to(val);
}

void Neural_Layer::randomize(int lowerBound, int upperBound, int decimal_precision){
    this->weights.randomize(lowerBound, upperBound, decimal_precision);
    this->biases.randomize(lowerBound, upperBound, decimal_precision);
}
