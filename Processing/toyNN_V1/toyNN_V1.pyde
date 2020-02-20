from NeuralNetwork import *
import os

inputs = [[0,0],[10,10],[4,4],[6,6],[2,1],[8,5],[5,7.5],[1,6],[6,1],[8,8],[0,8]]
targets = [[0],[1],[0],[1],[0],[1],[1],[0],[0],[1],[0]]

network = myNN(2,2,1)    

for x in range(50000):
    i = floor(random(0,11))
    network.train(inputs[i], targets[i])

output = network.predict([10,10])[0]
print(output)
output = network.predict([0,1])[0]
print(output)
output = network.predict([5.5,4.5])[0]

print(output)
if output > 0.5:
    os.system("say The flower is blue")
else:
    os.system("say The flower is red")
