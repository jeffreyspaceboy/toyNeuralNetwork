from Layer import *

class NeuralNetwork:
    def __init__(self, numNodes):
        self.numNodes = numNodes
        self.layers = []
        for i in range(len(numNodes)-1):
            self.layers.append(Layer(numNodes[i],numNodes[i+1]))
            self.layers[i].randomize(-1,1);
            
        self.learningRate = 0.2;
        self.trainingRuns = 5000;
        self.setActivationFunction(Sigmoid)
      
    def setActivationFunction(self, func = Sigmoid):
        self.activationFunction = func;
        for i in range(len(self.layers)):
            self.layers[i].setActivationFunction(Sigmoid);
    
    def feedForward(self, inputData):
        inputs = fromArray(inputData);
        self.layers[0].setInputs(inputs, False);
        for i in range(1,len(self.layers)):
            self.layers[i].setInputs(self.layers[i-1].solveForOutputs(), False);
        return (self.layers[len(self.layers)-1].solveForOutputs());
    
    def predict(self, inputArray):
        return self.feedForward(inputArray).toArray();
    
    def train(self, inputData, targetData):
        if((len(inputData[0]) != self.numNodes[0]) or (len(targetData[0]) != self.numNodes[-1])):
            print("ERROR: Training data dimentions do not match network dimentions.");
            exit();
        else:
            for i in range(self.trainingRuns): #Repeat until model has ran for desired number of training runs
                x = floor(random(0,len(inputData)-1));
                trainingOutputs = self.feedForward(inputData[x]); #Matrix of outputs from the training run
                trainingTargets = fromArray(targetData[x]);  #Matrix of targets from the training run
                trainingTargets = ~trainingTargets;
                
                self.layers[len(self.layers)-1].outputError = trainingTargets - trainingOutputs;
                self.layers[len(self.layers)-1].outputs = trainingOutputs;
                
                for k in range((len(self.layers)-1),0,-1):
                    self.layers[k].gradient = Map(self.layers[k].outputs, self.activationFunction.dfunc);
                    self.layers[k].gradient = (self.layers[k].gradient ** self.layers[k].outputError) * self.learningRate;
                    self.layers[k].weightsDelta = self.layers[k].gradient * (~self.layers[k].inputs);
                    self.layers[k].weights = self.layers[k].weights + self.layers[k].weightsDelta;
                    self.layers[k].biases = self.layers[k].biases + self.layers[k].gradient;
                    self.layers[k].inputError = (~self.layers[k].weights) * self.layers[k].outputError;
                    self.layers[k-1].outputError = self.layers[k].inputError;
                    self.layers[k-1].outputs = self.layers[k].inputs;
                    
                    
