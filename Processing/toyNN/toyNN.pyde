from NeuralNetwork import *
from Image import *
import os

inputs = [[0,0],[10,10],[4,4],[6,6],[2,1],[8,5],[5,7],[1,6],[6,1],[8,8],[0,8]];
targets = [[0],[1],[0],[1],[0],[1],[1],[0],[0],[1],[0]];

numNodes = [2,2,1];


def setup():
    global myImage
    size(200, 200);
    myImage = Image("../../trainingData/8/43is8.jpg");
    
    myNetwork = NeuralNetwork(numNodes);  
    myNetwork.trainingRuns = 100;
    myNetwork.fromFile("../../savedNeuralNetworks/Test.txt")
    #myNetwork.resetWeights();
    
    #myNetwork.train(inputs, targets);
    
    output = myNetwork.predict([10,10])[0];
    print(output)
    output = myNetwork.predict([0,0])[0];
    print(output)
    output = myNetwork.predict([5.5,4.5])[0];
    
    print(output)
    if output > 0.5:
        print("The flower is blue")
        # os.system("say The flower is blue");
    else:
        print("The flower is red")
        # os.system("say The flower is red");
    myNetwork.toFile("../../savedNeuralNetworks/Test.txt");
    
def draw():
    global myImage
    background(0)
    myImage.show()
