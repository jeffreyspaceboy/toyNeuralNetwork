//
//  Layer.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Layer.hpp"

Layer::Layer(){
    //Do Nothing
}

Layer::Layer(int numStartNodes,int numEndNodes){
    Matrix inputs(numStartNodes,1);
    Matrix weights(numEndNodes,numStartNodes);
    Matrix biases(numEndNodes,1);
    Matrix outputs(numEndNodes,1);
    this->inputs = inputs;
    this->weights = weights;
    this->biases = biases;
    this->outputs = outputs;
}

Layer::Layer(const Layer &obj){
    //std::cout<<"STATUS: Copying Layer"<<std::endl;
    this->inputs = obj.inputs;
    this->weights = obj.weights;
    this->biases = obj.biases;
    this->outputs = obj.outputs;
}

Layer::~Layer(void){
    //std::cout<<"STATUS: Clearing Layer"<<std::endl;
}

void Layer::randomize(int lowerBound, int upperBound){
    this->weights.randomize(lowerBound, upperBound);
    this->biases.randomize(lowerBound, upperBound);
}

void Layer::setInputs(Matrix data, bool doTranspose){
    this->inputs = data;
    if(doTranspose)
        this->inputs.transpose();
}

Matrix Layer::getOutputs(){
    randomize(-15, 15);

    //this->inputs.print();
    //this->weights.print();
    //this->outputs.print();
    //this->biases.print();
    
    this->outputs = this->outputs.crossProduct(this->weights,this->inputs);
    //this->outputs.print();
    //this->biases.print();
    
    this->outputs.add(this->biases);
    this->outputs.sigmoid();
    return this->outputs;
}

Matrix Layer::getInputs(){
    return this->inputs;
}

Matrix Layer::getWeights(){
    return this->weights;
}

Matrix Layer::getBiases(){
    return this->biases;
}

//Matrix outError;
//outError = outError.subtract();
