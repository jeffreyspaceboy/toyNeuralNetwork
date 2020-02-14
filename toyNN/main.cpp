//
//  main.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include <iostream>
#include "NeuralNetwork.hpp"

std::vector<std::vector<double>> inputs =
{{184,86,77},{222,152,11},{240,237,58},{91,240,58},{9,184,175},{92,106,230},{164,48,227},{232,5,194}}; //Input trainging data.

std::vector<std::vector<double>> targets =
{{1,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0},{0,0,1,0,0,0,0,0},{0,0,0,1,0,0,0,0},{0,0,0,0,1,0,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,1}}; //Correct output values for the input training data.
//Red,Orange,Yellow,Green,Cyan,Blue,Purple,Pink

std::vector<std::vector<double>> checkInputs =
{{189,51,51},{255,128,0},{214,204,17}};


std::vector<int> numNodes = {3,5,5,8}; //2 Inputs, 2 Hidden, and 1 Output

int main(){
    NeuralNetwork myToyNN(numNodes);
    myToyNN.train(inputs, targets);
    std::cout<<"STATUS: Finishing..."<<std::endl;
    return 0;
}

//IDEAS:
/*
- What if there is no activation function, but instead different ranges of values at one node meant different things?
   - Kind of like how touching can feel good on skin, but pressing hard can hurt.
 */


