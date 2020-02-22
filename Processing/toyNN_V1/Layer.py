from Matrix import *

class Layer:
    def __init__(self, numStartNodes, numEndNodes):
        self.inputs = Matrix(numStartNodes, 1);
        self.weights = Matrix(numEndNodes, numStartNodes);
        self.biases = Matrix(numEndNodes, 1);
        self.outputs = Matrix(numEndNodes, 1);
        
        self.outputError = Matrix(numEndNodes,1);
        self.gradient = Matrix(numEndNodes,1);
        self.weightsDelta = Matrix(numEndNodes,numStartNodes);
        self.inputError = Matrix(numStartNodes,1);
    def randomize(self, lowerBound, upperBound):
        self.weights.randomize(lowerBound, upperBound);
        self.biases.randomize(lowerBound, upperBound);
    
    
