from Matrix import *
from ActivationFunction import *

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
    
    def setActivationFunction(self, func):
        self.activationFunction = func
        
    def randomize(self, lowerBound, upperBound):
        self.weights.randomize(lowerBound, upperBound);
        self.biases.randomize(lowerBound, upperBound);
        
    def setInputs(self, data, doTranspose):
        self.inputs = data;
        if doTranspose:
            self.inputs = ~self.inputs;

    def solveForOutputs(self):
        self.outputs = (self.weights * self.inputs) + self.biases;
        self.outputs.Map(self.activationFunction.func);
        return self.outputs;

    
    
