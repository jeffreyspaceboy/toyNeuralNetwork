from Matrix import *

#IGEN

def sigmoid(x,r,c):
    return (1/(1 + exp(-x)))
def dSigmoid(y,r,c):
    return (y * (1-y))


class ActivationFunction:
    def __init__(self, func, dfunc):
        self.func = func
        self.dfunc = dfunc
    
Sigmoid = ActivationFunction(sigmoid,dSigmoid)

class NeuralNetwork:
    def __init__(self, inNodes, hidNodes, outNodes):
        self.inNodes = inNodes
        self.hidNodes = hidNodes
        self.outNodes = outNodes
        
        self.in2Hid_Weights = Matrix(self.hidNodes, self.inNodes)
        self.hid2Out_Weights = Matrix(self.outNodes, self.hidNodes)
        self.hid_Bias = Matrix(self.hidNodes, 1)
        self.out_Bias = Matrix(self.outNodes, 1)
        
        self.in2Hid_Weights.Randomize()
        self.hid2Out_Weights.Randomize()
        self.hid_Bias.Randomize()
        self.out_Bias.Randomize()
        
        self.learningRate = 0.2
        
        self.setActivationFunction()
      
    def setActivationFunction(self, func = Sigmoid):
        self.activationFunction = func
        
    def predict(self, inputArray):
        input = fromArray(inputArray)
        hidden = Multiply(self.in2Hid_Weights,input)
        hidden.Add(self.hid_Bias)
        hidden.Map(self.activationFunction.func)
        output = Multiply(self.hid2Out_Weights,hidden)
        output.Add(self.out_Bias)
        output.Map(self.activationFunction.func)
        return output.toArray()
    
    def train(self, inputArray, targetArray):
        input = fromArray(inputArray)
        target = fromArray(targetArray)

        hidden = Multiply(self.in2Hid_Weights,input)
        hidden.Add(self.hid_Bias)
        hidden.Map(self.activationFunction.func)
        output = Multiply(self.hid2Out_Weights,hidden)
        output.Add(self.out_Bias)
        output.Map(self.activationFunction.func)

        outError = Subtract(target,output)
        
        gradient = Map(output, self.activationFunction.dfunc)
        
        gradient.Multiply(outError)
        gradient.Multiply(self.learningRate)
        
        hiddenT = Transpose(hidden) 
        delta_hid2Out_Weights = Multiply(gradient,hiddenT)

        self.hid2Out_Weights.Add(delta_hid2Out_Weights)
        self.out_Bias.Add(gradient)
        
        hid2Out_WeightsT = Transpose(self.hid2Out_Weights)
        hidError = Multiply(hid2Out_WeightsT,outError)

        hidGradient = Map(hidden, self.activationFunction.dfunc)
        hidGradient.Multiply(hidError)
        hidGradient.Multiply(self.learningRate)
        
        inputT = Transpose(input)
        delta_in2Hid_Weights = Multiply(hidGradient,inputT)
        
        self.in2Hid_Weights.Add(delta_in2Hid_Weights)
        self.hid_Bias.Add(hidGradient)
    
