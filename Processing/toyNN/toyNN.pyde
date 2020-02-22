from NeuralNetwork import *
import os

inputs = [[0,0],[10,10],[4,4],[6,6],[2,1],[8,5],[5,7],[1,6],[6,1],[8,8],[0,8]];
targets = [[0],[1],[0],[1],[0],[1],[1],[0],[0],[1],[0]];

numNodes = [2,2,1];

myNetwork = NeuralNetwork(numNodes);  
myNetwork.trainingRuns = 10000;
myNetwork.fromFile("../../savedNeuralNetworks/Test.txt")
#myNetwork.resetWeights();

myNetwork.train(inputs, targets);

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

# def setup():
#     global lines
#     size(200, 200)
#     background(0)
#     stroke(255)
#     frameRate(12)
    

# def draw():
#     global index
#     if index < len(lines):
#         pieces = lines[index].split('\t')
#         if len(pieces) == 2:
#             x, y = int(pieces[0]) * 2, int(pieces[1]) * 2
#             point(x, y)
#         # Go to the next line for the next run through draw()
#         index = index + 1
