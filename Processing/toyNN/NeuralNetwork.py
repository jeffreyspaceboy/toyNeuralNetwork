from Layer import *

class NeuralNetwork:
    def __init__(self, numNodes):
        self.numNodes = numNodes
        self.layers = []
        for i in range(len(numNodes)-1):
            self.layers.append(Layer(numNodes[i],numNodes[i+1]))
        # self.resetWeights();
        self.learningRate = 0.2;
        self.trainingRuns = 1000;
        self.setActivationFunction(Sigmoid)
    def resetWeights(self):
        for i in range(len(self.numNodes)-1):
            self.layers[i].randomize(-1, 1);
    def setActivationFunction(self, func = Sigmoid):
        self.activationFunction = func;
        for i in range(len(self.layers)):
            self.layers[i].setActivationFunction(Sigmoid);
    def toFile(self, fileName):
        fileString = "";
        # self.layers[0].weights.Print()
        # self.layers[0].biases.Print()
        # self.layers[1].weights.Print()
        # self.layers[1].biases.Print()
        for i in range(len(self.layers)):
            numRows = self.layers[i].weights.rows;
            numCols = self.layers[i].weights.cols;
            fileString = fileString + "~\n" + str(i) + " 0 " + str(numRows) + " " + str(numCols) + "\n";
            for y in range(numRows):
                for x in range(numCols-1):
                    fileString = fileString + str(self.layers[i].weights.data[y][x]) + " ";
                fileString = fileString + str(self.layers[i].weights.data[y][numCols-1]) + "\n";
            numRows = self.layers[i].biases.rows;
            numCols = self.layers[i].biases.cols;
            fileString = fileString + "~\n" + str(i) + " 1 " + str(numRows) + " " + str(numCols) + "\n";
            for y in range(numRows):
                for x in range(numCols-1):
                    fileString = fileString + str(self.layers[i].biases.data[y][x]) + " ";
                fileString = fileString + str(self.layers[i].biases.data[y][numCols-1]) + "\n";
        saveBytes(fileName, fileString);
                                    
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
        else:
            for i in range(self.trainingRuns): #Repeat until model has ran for desired number of training runs
                x = floor(random(0,len(inputData)-1));
                trainingOutputs = self.feedForward(inputData[x]); #Matrix of outputs from the training run
                trainingTargets = fromArray(targetData[x]);  #Matrix of targets from the training run
                trainingTargets = ~trainingTargets;
                
                self.layers[len(self.layers)-1].outputError = trainingTargets - trainingOutputs;
                self.layers[len(self.layers)-1].outputs = trainingOutputs;
                
                for k in range((len(self.layers)-1),0,-1):
                    self.layers[k].gradient = (((Map(self.layers[k].outputs, self.activationFunction.dfunc)) ** self.layers[k].outputError) * self.learningRate); #Caculate gradient
                    self.layers[k].weightsDelta = self.layers[k].gradient * (~self.layers[k].inputs);
                    self.layers[k].weights = self.layers[k].weights + self.layers[k].weightsDelta;
                    self.layers[k].biases = self.layers[k].biases + self.layers[k].gradient;
                    self.layers[k].inputError = (~self.layers[k].weights) * self.layers[k].outputError;
                    self.layers[k-1].outputError = self.layers[k].inputError;
                    self.layers[k-1].outputs = self.layers[k].inputs;
    
    def fromFile(self, fileName): 
        lines = loadStrings(fileName);
        matrixInfo = [0,0,0,0]
        newMatrix = False
        i = 0
        while i < len(lines):
            pieces = lines[i].split(' ');
            if (pieces[0] == "~"):
                i += 1;
                pieces = lines[i].split(' ');
                for j in range(len(pieces)):
                    matrixInfo[j] = int(pieces[j]);
                i += 1;
            else:
                for y in range(matrixInfo[2]):
                    pieces = lines[i].split(' ');
                    for x in range(matrixInfo[3]):
                        if(matrixInfo[1]==0):
                            self.layers[matrixInfo[0]].weights.data[y][x] = float(pieces[x]);
                        elif(matrixInfo[1]==1):
                            self.layers[matrixInfo[0]].biases.data[y][x] = float(pieces[x]);
                    i += 1;
        # self.layers[0].weights.Print()
        # self.layers[0].biases.Print()
        # self.layers[1].weights.Print()
        # self.layers[1].biases.Print()
                    

        
