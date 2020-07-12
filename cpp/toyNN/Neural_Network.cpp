//
//  Neural_Network.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Neural_Network.hpp"

//---Constructors---//
Neural_Network::Neural_Network(void){}

Neural_Network::Neural_Network(std::vector<unsigned int> neurons){
    this->neurons = neurons;
    for(unsigned int i = 0; i < (this->neurons.size()-1); i++){
        this->layers.push_back(Neural_Layer(this->neurons[i], this->neurons[i+1]));
    }
}

Neural_Network::Neural_Network(std::string name){
    this->name = name;
    this->get_file();
}


//---Copy Constructors---//
Neural_Network::Neural_Network(const Neural_Network &obj){
    this->name = ("Copy_of_" + obj.name);
    this->neurons = obj.neurons;
    for(int i=0; i < (this->neurons.size()-1) ; i++){
        this->layers.push_back(Neural_Layer(this->neurons[i], this->neurons[i+1]));
    }
}

Neural_Network::Neural_Network(const Neural_Network &obj, std::string new_name){
    this->name = new_name;
    this->neurons = obj.neurons;
    for(int i=0; i < (this->neurons.size()-1) ; i++){
        this->layers.push_back(Neural_Layer(this->neurons[i], this->neurons[i+1]));
    }
}


//---Destructors---//
Neural_Network::~Neural_Network(void){
    this->save_file(this->name);
}


//---Set---//
void Neural_Network::set_name(std::string name){ this->name = name; }

//---Get---//
std::string Neural_Network::get_name(void){ return this->name; }


//---File_Write---//
void Neural_Network::save_file(){ this->save_file(this->name); }

void Neural_Network::save_file(std::string name){
    /* File Format
        Array Containing Neruon Structure
        ~
        Current_Layer   Select_Weights   X_Size   Y_Size   Z_Size
        Row of Weights Data
        ~
        Current_Layer    Select_Biases   X_Size   Y_Size   Z_Size
        Row of BiasesData
     
        ~
        ...
    */
    std::ofstream file;
    file.open(name);
    unsigned int i,j;
    for(i = 0; i < this->neurons.size(); i++){
        file << this->neurons[i] << " ";
    }
    file << "\n";
    for(i = 0; i < this->layers.size(); i++){
        file << "~\n" << i << " " << 0 <<" ";
        Shape weights_shape(this->layers[i].weights.get_shape());
        for(j = 0; j < sizeof(weights_shape.d); j++){
            file << weights_shape.d[j] << " ";
        }
        file << "\n";
        for(j = 0; j < weights_shape.size; j++){
            file << this->layers[i].weights.get_cell(j)<<" ";
        }
        file << "\n~\n" << i << " " << 1 <<" ";
        Shape biases_shape(this->layers[i].biases.get_shape());
        for(j = 0; j < sizeof(biases_shape.d); j++){
            file << biases_shape.d[j] << " ";
        }
        file << "\n";
        for(j = 0; j < biases_shape.size; j++){
            file << this->layers[i].biases.get_cell(j)<<" ";
        }
        file << "\n";
    }
    file.close();
}


//---File_Read---//
void Neural_Network::get_file(void){ this->get_file(this->name); }

void Neural_Network::get_file(std::string fileName){
    int neuronsInFile = this->checkNumNodesInFile();
    if(neuronsInFile == 0){
        std::cout<<"WARNING: File data dimentions do not match this Neural Network."<<std::endl;
        std::cout<<"Would you like to override your current network? (y:n)"<<std::endl;
        char ans;
        std::cin >> ans;
        if(ans=='y' || ans=='Y'){
            this->layers.clear();
            this->neurons.clear();
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
        for(int i=0; i<(layers.size()); i++)
            this->layers[i].randomize(-1, 1);
    }
}



void Neural_Network::setup_from_file(void){
    std::ifstream savedFile;
    savedFile.open(this->fileName);
    if(savedFile.is_open()){
        int matrixInfo[4];
        std::string scannedValue;
        std::vector<int> neurons;
        while(!savedFile.eof()){
            std::getline(savedFile, scannedValue);
            if(scannedValue == "~"){
                for(int j=0;j<4;j++){
                    std::getline(savedFile, scannedValue, ' ');
                    matrixInfo[j] = std::stoi(scannedValue);
                }
                if(matrixInfo[1]==0){
                    if(matrixInfo[0] == 0){
                        neurons.push_back(matrixInfo[3]);
                    }
                    neurons.push_back(matrixInfo[2]);
                }
            }
        }
        this->neurons = neurons;
        savedFile.close();
    } else {
        std::cout<<"ERROR: Could not open file."<<std::endl;
        exit(1);
    }
    for(int i=0; i < (this->neurons.size()-1) ; i++){
        Layer newLayer(this->neurons[i], this->neurons[i+1]);
        this->layers.push_back(newLayer);
    }
}



void Neural_Network::train(std::vector<std::vector<double>> inputData, std::vector<std::vector<double>> targetData){
    if((inputData[0].size() != this->neurons.front()) || (targetData[0].size() != this->neurons.back())){
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
            
            Tensor trainingOutputs(this->feedForward(trainingInput)); //Tensor of outputs from the training run
            Tensor trainingTargets(trainingTarget);  //Tensor of targets from the training run
            trainingTargets = trainingTargets.transposed();
            
            this->layers[this->layers.size()-1].outputError = trainingTargets - trainingOutputs;
            this->layers[this->layers.size()-1].outputs = trainingOutputs;
            
            for(unsigned long int k=this->layers.size()-1; k>0 ; k--){
                this->layers[k].gradient = this->layers[k].outputs;
                this->layers[k].gradient.dSigmoid();
                this->layers[k].gradient = this->layers[k].gradient ->* this->layers[k].outputError;
                this->layers[k].gradient = this->layers[k].gradient * this->learningRate;
                this->layers[k].inputsT = this->layers[k].inputs.transposed();
                Tensor delt(this->layers[k].gradient * this->layers[k].inputsT);
                this->layers[k].setWeightsDelta(delt);
                this->layers[k].weights = this->layers[k].weights + this->layers[k].weightsDelta;
                this->layers[k].biases = this->layers[k].biases + this->layers[k].gradient;
                this->layers[k].weightsT = this->layers[k].weights.transposed();
                this->layers[k].inputError = this->layers[k].weightsT * this->layers[k].outputError;
                this->layers[k-1].outputError = this->layers[k].inputError;
                this->layers[k-1].outputs = this->layers[k].inputs;
            }
        }
        
    }
}

//---Predict---//
Tensor Neural_Network::feed_forward(Tensor input_data){
    Tensor inputs(inputData);
    this->layers.front().setInputs(inputs, true);
    for(int j=1; j < this->layers.size(); j++){
        this->layers[j].setInputs(this->layers[j-1].solveForOutputs(), false);
    }
    return (this->layers[this->layers.size()-1].solveForOutputs());
}

Tensor Neural_Network::predict(Tensor input_data){
    if(inputData[0].size() > this->neurons.front()){
        std::cout<<"ERROR: Too many input nodes"<<std::endl;
        exit(1);
    } else if (inputData[0].size() < this->neurons.front()){
        std::cout<<"ERROR: Too few input nodes"<<std::endl;
        exit(1);
    } else {
        Tensor finalOutput(this->feedForward(inputData));
        finalOutput.print();
    }
    return inputData;
}







