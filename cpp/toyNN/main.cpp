//
//  main.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 2/10/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

//#include <stdio.h>
#include <iostream>
//#include <sstream>
//#include "NeuralNetwork.hpp"
//#include "Matrix.hpp"
#include "Tensor.hpp"



//std::vector<std::vector<double>> inputs =
//{   {255,0,0},{252,43,43},{209,47,29},{207,21,0},{227,37,16},
//    {107,194,37},{134,242,46},{6,212,6},{20,227,65},{0,255,0},
//    {0,0,255},{28,126,237},{8,27,196},{53,79,222},{23,70,209},
//    {255,0,255},{235,42,196},{237,111,206},{194,25,138},{245,34,175},
//    {255,221,0},{224,197,20},{239,255,10},{232,232,19},{245,245,44},
//    {0,255,255},{32,199,185},{58,208,235},{7,224,159},{76,245,194}
//}; //Input trainging data.
//
//std::vector<std::vector<double>> targets =
//{{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,0,0},
// {0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},{0,1,0,0,0,0},
// {0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},{0,0,1,0,0,0},
// {0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},
// {0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},{0,0,0,0,1,0},
// {0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,1}
//}; //Correct output values for the input training data.
//
//std::vector<int> numNodes = {3,8,6};
//
//std::vector<std::vector<double>> checkInputs = {{2, 242, 170}};
//Red, Green, Blue, Magenta, Yellow, Cyan
int main( int argc, char** argv){
//    NeuralNetwork myToyNN(numNodes,"networkData/colorDetector.txt");
//    myToyNN.train(inputs, targets);
//    myToyNN.predict(checkInputs);
//    double A[] = {1,2,3,2,3,1,3,1,2,3,3,3,2,2,2,1,1,1};
//    double B[] = {3,3,3,2,2,2,1,1,1,1,2,3,2,3,1,3,1,2};
//
//    Tensor testTensorA(A,3,3,2,"Tensor A");
//    Tensor testTensorB(B,3,3,2,"Tensor B");
//
//    testTensorA.print();
//    printf("\n");
//    testTensorB.print();
//    printf("\n");
//    Tensor testTensorC = testTensorB ->* testTensorA;
//    testTensorC.set_name("Tensor C");
//
//    //printf("Dim: (%d, %d, %d)\n",testTensor.get_x_size(),testTensor.get_y_size(),testTensor.get_z_size());
//    testTensorA.print();
//    printf("\n");
//    testTensorB.print();
//    printf("\n");
//    testTensorC.print();
//
//
//    Tensor testTensorD = testTensorB * testTensorA;
//    printf("\n");
//    testTensorD.print();

    float a[] = {1,2,3,4,5,6};
    float b[] = {6,5,4,3,2,1};
    Tensor A(a,Shape(3,2));
    Tensor B(b,Shape(3,2));
    A.randomize(-1,1);
    A.print();
    printf("\n");
    B.print();
    printf("\n");
    Tensor C = ~A - 1;
    C.print();
    printf("Done\n");
    return 0;
}
