//
//  NeuralNetwork.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(){
    //Do Nothing
}

NeuralNetwork::NeuralNetwork(std::vector<int> numNodes){
    this->numNodes = numNodes; //Address = layer, value = number of nodes in layer
    for(int i=0; i < (this->numNodes.size()-1) ; i++){
        std::cout<<"---GENERATING LAYER:#"<<i+1<<"---"<<std::endl;
        Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
        this->layers.push_back(newLayer);
    }
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork &obj){
    std::cout<<"STATUS: Copying Neural Network"<<std::endl;
    this->numNodes = obj.numNodes; //Address = layer, value = number of nodes in layer
    for(int i=0; i < (this->numNodes.size()-1) ; i++){
        std::cout<<"---GENERATING LAYER:#"<<i+1<<"---"<<std::endl;
        Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
        this->layers.push_back(newLayer);
    }
}

NeuralNetwork::~NeuralNetwork(void){
    std::cout<<"STATUS: Clearing Neural Network"<<std::endl;
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
        std::vector<std::vector<double>> trainingInput;
        std::vector<std::vector<double>> trainingTarget;
        int x;
        for(int i=0; i < trainingRuns; i++){
            std::cout<<"----------Training Run: #"<<i+1<<"---------v"<<std::endl;
            x = rand() % (inputData.size());
            trainingInput.clear();
            trainingInput.push_back(inputData[x]);
            Matrix trainingInputs(trainingInput);
            //std::cout<<"Num of layers: "<<this->layers.size()<<std::endl;
            this->layers.front().setInputs(trainingInputs, true);
            for(int j=1; j < this->layers.size(); j++){
                //layers[j-1].getOutputs().print(); //Prints outputs at each layer
                this->layers[j].setInputs(this->layers[j-1].getOutputs(), false);
            }
            Matrix trainingOutputs(this->layers[this->layers.size()-1].getOutputs()); //Getting outputs from the training run
            
            trainingTarget.push_back(targetData[x]); //Setup a 2D vector with just the single target
            Matrix trainingTargets(trainingTarget);  //Put that 2D vector
            trainingTargets.transpose();
            
            //PROBABLY NEED TO PUT IN A FOR LOOP TO RUN THROUGH LAYERS
            //matrix Error = target - output //Start at output layer
            
            int layerNum = 2;
            
            layers[layerNum].outputError = trainingTargets - trainingOutputs;
            
            //matrix gradient = Map(dSigmoid(output))
            
            layers[layerNum].gradient = trainingOutputs;
            layers[layerNum].gradient.dSigmoid();
            
            
            layers[layerNum].gradient = layers[layerNum].gradient ->* layers[layerNum].outputError; //gradient = gradient * outError //Hadamard
            layers[layerNum].gradient = layers[layerNum].gradient * learningRate; //gradient = gradient * learningRate //Scalar

            
            //Traspose hidden matrix
            Matrix hiddenT(this->layers[layerNum].inputs); //THE NODES themselves
            hiddenT.transpose();

            //Delta weights hidden to out = gradient X hiddenTransposed
            Matrix temp(layers[layerNum].gradient * hiddenT);
            layers[layerNum].setWeightsDelta(temp);
            
            
            //hiddentoOutWeights = hiddentoOutWeights + deltaHidtoOutWeight
            layers[layerNum].weights = layers[layerNum].weights + layers[layerNum].weightsDelta;
            
            //outBias = outBias + gradient
            layers[layerNum].biases = layers[layerNum].biases + layers[layerNum].gradient;
            
            
            
            //hid2Out_WeightsT = Transpose(hid2Out_Weights)
            layers[layerNum].setWeightsTransposed();
            layers[layerNum].weights.print();
            layers[layerNum].weightsT.print();
            //layers[layerNum].outputError.print();
            //hidError = hid2Out_WeightsT X outError
            layers[layerNum].inputError = layers[layerNum].weightsT * layers[layerNum].outputError;
            
            

            //hidGradient = Map(hidden, dfunc)
            //hidGradient = hidGradient*hidError //Hadamard
            //hidGradient = hidGradient*learningRate //Scalar
            
            //inputT = Transpose(input)
            //delta_in2Hid_Weights = hidGradient X inputT
            
            //in2Hid_Weights = in2Hid_Weights + delta_in2Hid_Weights
            //hid_Bias = hid_Bias + hidGradient
            
            std::cout<<"----------Training Run: #"<<i+1<<"---------^"<<std::endl<<std::endl;
        }
        
    }
}

std::vector<std::vector<double>> NeuralNetwork::predict(std::vector<std::vector<double>> inputData){ //NOT SURE IF THIS IS RIGHT
    if(inputData[0].size() > this->numNodes.front()){
        std::cout<<"ERROR: Too many input nodes"<<std::endl;
        exit(1);
    } else if (inputData[0].size() < this->numNodes.front()){
        std::cout<<"ERROR: Too few input nodes"<<std::endl;
        exit(1);
    } else {
        for(int i=0; i < (this->numNodes.size()-1) ; i++){
            std::cout<<"---GENERATING LAYER:#"<<i+1<<"---"<<std::endl;
            Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
            this->layers.push_back(newLayer);
        }
        std::cout<<"----------Prediction Run---------v"<<std::endl;
        Matrix inputs(inputData);
        this->layers.front().setInputs(inputs, true);
        for(int j=1; j < this->layers.size(); j++){
            //layers[j-1].getOutputs().print(); //Prints outputs at each layer
            this->layers[j].setInputs(this->layers[j-1].getOutputs(), false);
        }
        this->layers[this->layers.size()-1].getOutputs().print();
        std::cout<<"----------Prediction Run---------^"<<std::endl<<std::endl;
    }
    return inputData;
}
