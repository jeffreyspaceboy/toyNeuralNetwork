//
//  NeuralNetwork.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "NeuralNetwork.hpp"
#include <sstream>
#include <fstream>

NeuralNetwork::NeuralNetwork(){}

NeuralNetwork::NeuralNetwork(std::vector<int> numNodes, std::string fileName){
    this->fileName = fileName;
    this->numNodes = numNodes;
    for(int i=0; i < (this->numNodes.size()-1) ; i++){
        Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
        this->layers.push_back(newLayer);
    }
    this->getWeightsFile();
}

NeuralNetwork::NeuralNetwork(std::string fileName){
    this->fileName = fileName;
    this->getWeightsFile();
}


NeuralNetwork::NeuralNetwork(const NeuralNetwork &obj){
    this->numNodes = obj.numNodes;
    for(int i=0; i < (this->numNodes.size()-1) ; i++){
        Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
        this->layers.push_back(newLayer);
    }
}

NeuralNetwork::~NeuralNetwork(void){this->saveWeightsFile(this->fileName);}

void NeuralNetwork::setupNetworkFromFile(){
    std::ifstream savedFile;
    savedFile.open(this->fileName);
    if(savedFile.is_open()){
        int matrixInfo[4];
        std::string scannedValue;
        std::vector<int> numNodes;
        while(!savedFile.eof()){
            std::getline(savedFile, scannedValue);
            if(scannedValue == "~"){
                for(int j=0;j<4;j++){
                    std::getline(savedFile, scannedValue, ' ');
                    matrixInfo[j] = std::stoi(scannedValue);
                }
                if(matrixInfo[1]==0){
                    if(matrixInfo[0] == 0){
                        numNodes.push_back(matrixInfo[3]);
                    }
                    numNodes.push_back(matrixInfo[2]);
                }
            }
        }
        this->numNodes = numNodes;
        savedFile.close();
    } else {
        std::cout<<"ERROR: Could not open file."<<std::endl;
        exit(1);
    }
    for(int i=0; i < (this->numNodes.size()-1) ; i++){
        Layer newLayer(this->numNodes[i], this->numNodes[i+1]);
        this->layers.push_back(newLayer);
    }
}

Matrix NeuralNetwork::feedForward(std::vector<std::vector<double>> inputData){
    Matrix inputs(inputData);
    this->layers.front().setInputs(inputs, true);
    for(int j=1; j < this->layers.size(); j++){
        this->layers[j].setInputs(this->layers[j-1].solveForOutputs(), false);
    }
    return (this->layers[this->layers.size()-1].solveForOutputs());
}

void NeuralNetwork::train(std::vector<std::vector<double>> inputData, std::vector<std::vector<double>> targetData){
    if((inputData[0].size() != this->numNodes.front()) || (targetData[0].size() != this->numNodes.back())){
        std::cout<<"ERROR: Training data dimentions do not match network dimentions."<<std::endl;
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
                
                this->layers[k].roundToThousandths();
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

int NeuralNetwork::checkNumNodesInFile(){
    std::ifstream savedFile;
    savedFile.open(fileName);
    if(savedFile.is_open()){
        int matrixInfo[4];
        std::string scannedValue;
        std::vector<int> numNodes;
        while(!savedFile.eof()){
            std::getline(savedFile, scannedValue);
            if(scannedValue == "~"){
                for(int j=0;j<4;j++){
                    std::getline(savedFile, scannedValue, ' ');
                    matrixInfo[j] = std::stoi(scannedValue);
                }
                if(matrixInfo[1]==0){
                    if(matrixInfo[0] == 0){
                        numNodes.push_back(matrixInfo[3]);
                    }
                    numNodes.push_back(matrixInfo[2]);
                }
            }
        }
        savedFile.close();
        if(this->numNodes == numNodes){
            return 1;
        }else{
            return 0;
        }
    } else {
        return 2;
    }
}

void NeuralNetwork::saveWeightsFile(std::string fileName){
    std::ofstream saveFile;
    saveFile.open(fileName);
    for(int i=0;i<(this->layers.size());i++){
        int numRows = (int)this->layers[i].weights.getNumRows();
        int numCols = (int)this->layers[i].weights.getNumCols();
        saveFile << "~\n";
        saveFile << i << " " << 0 <<" "<< numRows <<" "<< numCols <<" \n";
        for(int y=0;y<numRows;y++){
            //saveFile<<"[";
            for(int x=0;x<(numCols-1);x++){
                saveFile << this->layers[i].weights.getData(y, x)<<" ";
            }
            saveFile << this->layers[i].weights.getData(y, numCols-1)<<" \n";///<<std::endl;
        }
        saveFile << "~\n";
        numRows = (int)this->layers[i].biases.getNumRows();
        numCols = (int)this->layers[i].biases.getNumCols();
        saveFile << i << " " << 1 <<" "<< numRows <<" "<< numCols <<" \n";
        for(int y=0;y<numRows;y++){
            //saveFile<<"[";
            for(int x=0;x<(numCols-1);x++){
                saveFile << this->layers[i].biases.getData(y, x)<<" ";
            }
            saveFile << this->layers[i].biases.getData(y, numCols-1)<<" \n";///<<std::endl;
        }
        saveFile << "\n";
    }
    saveFile.close();
}

void NeuralNetwork::saveWeightsFile(){this->saveWeightsFile(this->fileName);}


void NeuralNetwork::getWeightsFile(std::string fileName){
    int numNodesInFile = this->checkNumNodesInFile();
    if(numNodesInFile == 0){
        std::cout<<"WARNING: File data dimentions do not match this Neural Network."<<std::endl;
        std::cout<<"Would you like to override your current network? (y:n)"<<std::endl;
        char ans;
        std::cin >> ans;
        if(ans=='y' || ans=='Y'){
            this->layers.clear();
            this->numNodes.clear();
            this->setupNetworkFromFile();
        }
    }
    std::ifstream savedFile;
    savedFile.open(fileName);
    if(savedFile.is_open()){
        int matrixInfo[4];
        std::string scannedValue;
        while(!savedFile.eof()){
            std::getline(savedFile, scannedValue);
            if(scannedValue == "~"){
                for(int j=0;j<4;j++){
                    std::getline(savedFile, scannedValue, ' ');
                    matrixInfo[j] = std::stoi(scannedValue);
                }
                for(int y=0;y<matrixInfo[2];y++){
                    for(int x=0;x<matrixInfo[3];x++){
                        std::getline(savedFile, scannedValue, ' ' );
                        if(matrixInfo[1]==0) {
                            this->layers[matrixInfo[0]].weights.setData(y, x, std::stod(scannedValue));
                        } else if(matrixInfo[1]==1) {
                            this->layers[matrixInfo[0]].biases.setData(y, x, std::stod(scannedValue));
                        }
                    }
                }
            }
        }
    } else {
        std::cout<<"ERROR: Could not open file. Error will be ignored, and file will be created later."<<std::endl;
    }
}

void NeuralNetwork::getWeightsFile(){this->getWeightsFile(this->fileName);}

