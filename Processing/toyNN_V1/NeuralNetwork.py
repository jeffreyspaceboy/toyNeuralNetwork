
from Layer import *
from ActivationFunction import *


class NeuralNetwork:
    def __init__(self, numNodes):
        self.layers = []
        for i in range(len(numNodes)-1):
            self.layers.append(Layer(numNodes[i],numNodes[i+1]))
        self.inNodes = numNodes[0]
        self.hidNodes = numNodes[1]
        self.outNodes = numNodes[2]
        
        self.in2Hid_Weights = Matrix(self.hidNodes, self.inNodes)
        self.hid2Out_Weights = Matrix(self.outNodes, self.hidNodes)
        self.hid_Bias = Matrix(self.hidNodes, 1)
        self.out_Bias = Matrix(self.outNodes, 1)
        
        self.in2Hid_Weights.randomize(-1,1)
        self.hid2Out_Weights.randomize(-1,1)
        self.hid_Bias.randomize(-1,1)
        self.out_Bias.randomize(-1,1)
        
        self.learningRate = 0.2
        
        self.setActivationFunction()
      
    def setActivationFunction(self, func = Sigmoid):
        self.activationFunction = func
        
    def predict(self, inputArray):
        input = fromArray(inputArray)
        hidden = self.in2Hid_Weights * input #Cross Product
        hidden = hidden + self.hid_Bias
        hidden.Map(self.activationFunction.func)
        output = self.hid2Out_Weights * hidden #Cross Product
        output = output + self.out_Bias
        output.Map(self.activationFunction.func)
        return output.toArray()
    
    def train(self, inputArray, targetArray):
        input = fromArray(inputArray)
        target = fromArray(targetArray)

        hidden = self.in2Hid_Weights * input #Cross Product
        hidden = hidden + self.hid_Bias
        hidden.Map(self.activationFunction.func)
        output = self.hid2Out_Weights * hidden #Cross Product
        output = output + self.out_Bias
        output.Map(self.activationFunction.func)

        outError = target - output
        
        gradient = Map(output, self.activationFunction.dfunc)
        
        gradient = gradient ** outError #Hadamard Product
        gradient = gradient * self.learningRate #Scalar Product
        
        delta_hid2Out_Weights = gradient * (~hidden) #Cross Product

        self.hid2Out_Weights = self.hid2Out_Weights + delta_hid2Out_Weights
        self.out_Bias = self.out_Bias + gradient
        
        hidError = (~self.hid2Out_Weights) * outError #Cross Product

        hidGradient = Map(hidden, self.activationFunction.dfunc)
        hidGradient = hidGradient ** hidError #Hadamard Product
        hidGradient = hidGradient * self.learningRate #Scalar Product
        
        delta_in2Hid_Weights = hidGradient * (~input) #Cross Product
        
        self.in2Hid_Weights = self.in2Hid_Weights + delta_in2Hid_Weights
        self.hid_Bias = self.hid_Bias + hidGradient
    
