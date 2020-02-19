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
    
    
    Matrix inputsT(1,numStartNodes);
    this->inputsT = inputsT;
    
    Matrix weightsT(numStartNodes, numEndNodes);
    this->weightsT = weightsT;
    
    Matrix outputError(numEndNodes,1);
    this->outputError = outputError;
    Matrix gradient(numEndNodes,1);
    this->gradient = gradient;
    Matrix weightsDelta(numEndNodes,numStartNodes);
    this->weightsDelta = weightsDelta;
    Matrix inputError(numStartNodes,1);
    this->inputError = inputError;
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
    this->outputs = this->outputs.crossProduct(this->weights,this->inputs);
    //this->outputs.print();
    this->outputs.vectorSum(this->biases);
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

void Layer::setWeightsDelta(Matrix &obj){
    this->weightsDelta = obj;
}

void Layer::setWeightsTransposed(){
    Matrix temp(this->weights);
    temp.transpose();
    this->weightsT = temp;
}

void Layer::setInputsTransposed(){
    Matrix temp(this->inputs);
    temp.transpose();
    this->inputsT = temp;
}

