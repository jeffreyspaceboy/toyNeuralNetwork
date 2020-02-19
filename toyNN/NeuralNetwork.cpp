//
//  NeuralNetwork.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(){}

NeuralNetwork::NeuralNetwork(std::vector<int> numNodes){
    this->numNodes = numNodes;
    for(int i=0; i < (this->numNodes.size()-1) ; i++){
        Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
        this->layers.push_back(newLayer);
    }
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &obj){
    this->numNodes = obj.numNodes;
    for(int i=0; i < (this->numNodes.size()-1) ; i++){
        Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
        this->layers.push_back(newLayer);
    }
}

NeuralNetwork::~NeuralNetwork(void){}

Matrix NeuralNetwork::feedForward(std::vector<std::vector<double>> inputData){
    Matrix inputs(inputData);
    this->layers.front().setInputs(inputs, true);
    for(int j=1; j < this->layers.size(); j++){
        this->layers[j].setInputs(this->layers[j-1].solveForOutputs(), false);
    }
    return (this->layers[this->layers.size()-1].solveForOutputs());
}

void NeuralNetwork::train(std::vector<std::vector<double>> inputData, std::vector<std::vector<double>> targetData){
    if(inputData[0].size() > this->numNodes.front()){
        std::cout<<"ERROR: Too many input nodes"<<std::endl;
        exit(1);
    } else if (inputData[0].size() < this->numNodes.front()){
        std::cout<<"ERROR: Too few input nodes"<<std::endl;
        exit(1);
    } else if (targetData[0].size() > this->numNodes.back()){
        std::cout<<"ERROR: Too many output target nodes"<<std::endl;
        exit(1);
    } else if (targetData[0].size() < this->numNodes.back()){
        std::cout<<"ERROR: Too few output target nodes"<<std::endl;
        exit(1);
    } else {
        int x;
        for(int i=0; i < trainingRuns; i++){ //Repeat until model has ran for desired number of training runs
            x = rand() % (inputData.size()-1); //Select a random training set.
            
            std::vector<std::vector<double>> trainingInput; //2D vector with single input set
            trainingInput.push_back(inputData[x]);
            std::vector<std::vector<double>> trainingTarget; //2D vector with single output set
            trainingTarget.push_back(targetData[x]);
            
            Matrix trainingOutputs(this->feedForward(trainingInput)); //Matrix of outputs from the training run
            Matrix trainingTargets(trainingTarget);  //Matrix of targets from the training run
            trainingTargets.transpose();
            
            this->layers[this->layers.size()-1].outputError = trainingTargets - trainingOutputs;
            this->layers[this->layers.size()-1].outputs = trainingOutputs;
            
            for(unsigned long int k=this->layers.size()-1; k>0 ; k--){
                this->layers[k].gradient = this->layers[k].outputs;
                this->layers[k].gradient.dSigmoid();
                this->layers[k].gradient = this->layers[k].gradient ->* this->layers[k].outputError;
                this->layers[k].gradient = this->layers[k].gradient * this->learningRate;
                this->layers[k].setInputsTransposed();
                Matrix delt(this->layers[k].gradient * this->layers[k].inputsT);
                this->layers[k].setWeightsDelta(delt);
                this->layers[k].weights = this->layers[k].weights + this->layers[k].weightsDelta;
                this->layers[k].biases = this->layers[k].biases + this->layers[k].gradient;
                this->layers[k].setWeightsTransposed();
                this->layers[k].inputError = this->layers[k].weightsT * this->layers[k].outputError;
                this->layers[k-1].outputError = this->layers[k].inputError;
                this->layers[k-1].outputs = this->layers[k].inputs;
            }
        }
        
    }
}

std::vector<std::vector<double>> NeuralNetwork::predict(std::vector<std::vector<double>> inputData){
    if(inputData[0].size() > this->numNodes.front()){
        std::cout<<"ERROR: Too many input nodes"<<std::endl;
        exit(1);
    } else if (inputData[0].size() < this->numNodes.front()){
        std::cout<<"ERROR: Too few input nodes"<<std::endl;
        exit(1);
    } else {
        Matrix finalOutput(this->feedForward(inputData));
        finalOutput.print();
    }
    return inputData;
}
