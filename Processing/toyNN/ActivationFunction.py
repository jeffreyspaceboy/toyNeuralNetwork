def sigmoid(x,r,c):
    return (1/(1 + exp(-x)));
def dSigmoid(y,r,c):
    return (y * (1-y));

class ActivationFunction:
    def __init__(self, func, dfunc):
        self.func = func;
        self.dfunc = dfunc;
    
Sigmoid = ActivationFunction(sigmoid,dSigmoid);
