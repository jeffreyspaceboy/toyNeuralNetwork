class Matrix():
    def __init__(self, rows, cols):
        self.rows = rows;
        self.cols = cols;
        self.data = [];
        for r in range(self.rows):
            self.data.append([]);
            for c in range(self.cols):
                self.data[r].append(0);
        
    def randomize(self,lowerBound, upperBound):
        self.Map(lambda e,r,c: random(lowerBound,upperBound));    

    def __add__(self, b):
        if isinstance(b, Matrix):
            if (self.rows != b.rows)or(self.cols != b.cols):
                print("ERROR: Matrix dimentions must match.");
                return;
            result = Map(self,lambda e,r,c: e + b.data[r][c]);
            return result;
        else:
            result = Map(self,lambda e,r,c: e + b);
            return result;
        
    def __iadd__(self, b):
        if isinstance(b, Matrix):
            if (self.rows != b.rows)or(self.cols != b.cols):
                print("ERROR: Matrix dimentions must match.");
                return;
            result = Map(self,lambda e,r,c: e + b.data[r][c]);
            return result;
        else:
            result = Map(self,lambda e,r,c: e + b);
            return result;
        
    def __sub__(self, b):
        if isinstance(b, Matrix):
            if (self.rows != b.rows)or(self.cols != b.cols):
                print("ERROR: Matrix dimentions must match.");
                return;
            result = Map(self,lambda e,r,c: e - b.data[r][c]);
            return result;
        else:
            result = Map(self,lambda e,r,c: e - b);
            return result;
    def __mul__(self, b):
        if isinstance(b, Matrix): #Cross product
            if (self.cols != b.rows):
                print('ERROR: Columns of first matrix must match rows of second matrix.');
                return;
            else:
                result = Matrix(self.rows,b.cols);
                for r in range(result.rows):
                    for c in range(result.cols):
                        sum = 0;
                        for k in range(self.cols):
                            sum += self.data[r][k] * b.data[k][c];
                        result.data[r][c] = sum;
                return result; 
        else: #Scalar Product
            return Map(self,lambda e,r,c: e*b);
        
    def __pow__(self, b):
        if isinstance(b, Matrix):
            if (self.rows != b.rows)or(self.cols != b.cols):
                print("ERROR: Matrix dimentions must match.");
                return;
            #Hadamard product
            return self.Map(lambda e,r,c: e*b.data[r][c]);
        else:
            #Exponential product
            return self.Map(lambda e,r,c: e**b);  
                   
    def __invert__(self):
        return Map(Matrix(self.cols, self.rows),lambda e,r,c: self.data[c][r]);
    
    def Print(self):
        for r in range(self.rows):
            print(self.data[r]);
            
    def toArray(self):
        arr = [];
        for r in range(self.rows):
            for c in range(self.cols):
                arr.append(self.data[r][c]);
        return arr;
    
    def Map(self,func):
        for r in range(self.rows):
            for c in range(self.cols):
                val = self.data[r][c];
                self.data[r][c] = func(val, r, c);
        return self;
           
def fromArray(arr):
    return Map(Matrix(len(arr), 1),lambda e,r,c: arr[r]);    
    #return Map(Matrix(len(arr), len(arr[0])),lambda e,r,c: arr[r][c]);   
def Map(matrix, func):
    return Matrix(matrix.rows, matrix.cols).Map(lambda e,r,c: func(matrix.data[r][c], r, c));
