//
//  NeuralNetwork.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include "Layer.hpp"
#include "Matrix.hpp"

class NeuralNetwork{
    private:
        std::vector<int> numNodes; //Address = layer, value = number of nodes in layer
        std::string fileName = "myNeuralNetwork.txt";
        std::vector<Layer> layers;
        double learningRate = 0.2;
        int trainingRuns = 1000;
    public:
        NeuralNetwork();
        NeuralNetwork(std::vector<int> numNodes,std::string fileName);
        NeuralNetwork(std::string fileName);
        NeuralNetwork(const NeuralNetwork &obj);
        ~NeuralNetwork();
        void setupNetworkFromFile();
        Matrix feedForward(std::vector<std::vector<double>> inputData);
        void train(std::vector<std::vector<double>> inputData, std::vector<std::vector<double>> targetData);
        std::vector<std::vector<double>> predict(std::vector<std::vector<double>> inputData);
       
        void saveWeightsFile(std::string fileName);
        void saveWeightsFile();
        void getWeightsFile(std::string fileName);
        void getWeightsFile();
    
        int checkNumNodesInFile();
};

#endif /* NeuralNetwork_hpp */
