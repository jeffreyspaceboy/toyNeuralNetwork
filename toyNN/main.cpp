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
{{255,0,0},{201,89,89},{230,71,39},{240,17,17},{219,28,41},
 {255,153,0},{235,175,87},{217,114,4},{222,131,47},{204,119,8},
 {204,204,8},{255,255,0},{191,191,63},{237,245,88},{187,196,6},
 {128,255,0},{2,247,64},{3,148,39},{121,242,151},{85,140,66},
 {0,255,187},{66,138,119},{128,229,232},{0,187,194},{58,224,213},
 {0,115,255},{92,107,224},{11,72,214},{7,106,219},{56,142,217},
 {128,0,255},{175,123,227},{71,0,186},{123,42,209},{109,38,153},
 {255,0,238},{214,47,203},{235,124,204},{227,11,223},{237,149,201},
}; //Input trainging data.

std::vector<std::vector<double>> targets =
{{1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0},
 {0,1,0,0,0,0,0,0},{0,1,0,0,0,0,0,0},{0,1,0,0,0,0,0,0},{0,1,0,0,0,0,0,0},{0,1,0,0,0,0,0,0},
 {0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,0},
 {0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,0},
 {0,0,0,0,1,0,0,0},{0,0,0,0,1,0,0,0},{0,0,0,0,1,0,0,0},{0,0,0,0,1,0,0,0},{0,0,0,0,1,0,0,0},
 {0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,0},
 {0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,0},
 {0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,1}
}; //Correct output values for the input training data.
//Red,Orange,Yellow,Green,Cyan,Blue,Purple,Pink

std::vector<std::vector<double>> checkInputs =
{{0,0,255}};

/*

std::vector<std::vector<double>> inputs =
{
    {0,0},{10,10},{4,4},{6,6},{2,1},{8,5},{5,7.5},{1,6},{6,1},{8,8},{0,8}
}; //Input trainging data.

std::vector<std::vector<double>> targets =
{
    {0},{1},{0},{1},{0},{1},{1},{0},{0},{1},{0}
}; //Correct output values for the input training data.

std::vector<std::vector<double>> checkInputs =
{
    {0,0},{2,1},{10,10},{5,7.5}
};
 
 */

std::vector<int> numNodes = {3,6,6,8};

int main(){
    NeuralNetwork myToyNN(numNodes);
    //myToyNN.train(inputs, targets);
    //myToyNN.predict(checkInputs);
    myToyNN.saveWeightsFile();
    return 0;
}

//IDEAS:
/*
- What if there is no activation function, but instead different ranges of values at one node meant different things?
   - Kind of like how touching can feel good on skin, but pressing hard can hurt.
 */


