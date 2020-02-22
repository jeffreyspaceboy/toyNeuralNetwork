from NeuralNetwork import *
import os
inputs = [[[0],[0]],[[10],[10]],[[4],[4]],[[6],[6]],[[2],[1]],[[8],[5]],[[5],[7]],[[1],[6]],[[6],[1]],[[8],[8]],[[0],[8]]];
#inputs = [[0,0],[10,10],[4,4],[6,6],[2,1],[8,5],[5,7],[1,6],[6,1],[8,8],[0,8]];
targets = [[[0]],[[1]],[[0]],[[1]],[[0]],[[1]],[[1]],[[0]],[[0]],[[1]],[[0]]];

numNodes = [2,2,1];

myNetwork = NeuralNetwork(numNodes);  

for x in range(5000):
    i = floor(random(0,len(inputs)))
    myNetwork.train(inputs[i], targets[i])

output = myNetwork.predict([[10],[10]])[0]
print(output)
output = myNetwork.predict([[0],[1]])[0]
print(output)
output = myNetwork.predict([[5.5],[4.5]])[0]

print(output)
if output > 0.5:
    os.system("say The flower is blue")
else:
    os.system("say The flower is red")