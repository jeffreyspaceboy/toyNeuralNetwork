//
//  main.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include <iostream>
#include "NeuralNetwork.hpp"
#include <CoreGraphics/CoreGraphics.h>

std::vector<std::vector<double>> inputs =
{   {255,0,0},{252,43,43},{209,47,29},{207,21,0},{227,37,16},
    {107,194,37},{134,242,46},{6,212,6},{20,227,65},{0,255,0},
    {0,0,255},{28,126,237},{8,27,196},{53,79,222},{23,70,209},
    {255,0,255},{235,42,196},{237,111,206},{194,25,138},{245,34,175},
    {255,221,0},{224,197,20},{239,255,10},{232,232,19},{245,245,44},
    {0,255,255},{32,199,185},{58,208,235},{7,224,159},{76,245,194}
}; //Input trainging data.


std::vector<std::vector<double>> targets =
{{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},
 {0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},
 {0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},
 {0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},
 {0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},
 {0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1}
}; //Correct output values for the input training data.
//Red,Green,Blue,Magenta,Yellow,Cyan

std::vector<std::vector<double>> checkInputs = {{2, 242, 170}};
 //Red,Green,Blue,Magenta,Yellow,Cyan

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
    {0,0},{2,1},{10,10},{5,7.5},{1,4},{7,6}
};
 */

std::vector<int> numNodes = {3,8,6};

int main(){
    NeuralNetwork myToyNN(numNodes,"testing.txt");
    //myToyNN.train(inputs, targets);
    myToyNN.predict(checkInputs);
    std::cout<<"Done"<<std::endl;
    return 0;
}

//IDEAS:
/*
- What if there is no activation function, but instead different ranges of values at one node meant different things?
   - Kind of like how touching can feel good on skin, but pressing hard can hurt.
 */



