//
//  NeuralNetwork.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef NeuralNetwork_hpp
#define NeuralNetwork_hpp

#include <stdio.h>
#include "Layer.hpp"
#include "Matrix.hpp"

class NeuralNetwork{
    private:
        std::vector<int> numNodes; //Address = layer, value = number of nodes in layer
        std::vector<Layer> layers;
        double learningRate = 0.2;
        int trainingRuns = 50000;
    public:
        NeuralNetwork();
        NeuralNetwork(std::vector<int> numNodes);
        NeuralNetwork(const NeuralNetwork &obj);
        ~NeuralNetwork();
        Matrix feedForward(std::vector<std::vector<double>> inputData);
        void train(std::vector<std::vector<double>> inputData, std::vector<std::vector<double>> targetData);
        std::vector<std::vector<double>> predict(std::vector<std::vector<double>> inputData);
       
        void saveWeightsFile(std::string fileName = "myNeuralNetwork.txt");
        void getWeightsFile(std::string fileName = "myNeuralNetwork.txt");
};

#endif /* NeuralNetwork_hpp */
