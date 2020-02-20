class Matrix():
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.data = []
        for r in range(self.rows):
            self.data.append([])
            for c in range(self.cols):
                self.data[r].append(0)
    def Map(self,func):
        for r in range(self.rows):
            for c in range(self.cols):
                val = self.data[r][c]
                self.data[r][c] = func(val, r, c)
        return self

    def toArray(self):
        arr = []
        for r in range(self.rows):
            for c in range(self.cols):
                arr.append(self.data[r][c])
        return arr

    def Randomize(self):
        return Map(self,lambda e,r,c: random(-1,1))     

    def Add(self, b):
        if isinstance(b, Matrix):
            if (self.rows != b.rows)or(self.cols != b.cols):
                print('Columns and Rows of A must match Columns and Rows of B.')
                return
            return self.Map(lambda e,r,c: e + b.data[r][c])
        else:
            return self.Map(lambda e,r,c: e + b)
                
    def Multiply(self, b):
        if isinstance(b, Matrix):
            if (self.rows != b.rows)or(self.cols != b.cols):
                print('Columns and Rows of A must match Columns and Rows of B.')
                return
            #Hadamard product
            return self.Map(lambda e,r,c: e*b.data[r][c])
        else:
            #Scalar product
            return self.Map(lambda e,r,c: e*b)
    
    def Print(self):
        print(self.data)
        
        
def fromArray(arr):
    return Map(Matrix(len(arr), 1),lambda e,r,c: arr[r]);
    
def Subtract(a, b):
    if (a.rows != b.rows)or(a.cols != b.cols):
        print('Columns and Rows of A must match Columns and Rows of B.');
    else:
        #Return a new Matrix a-b
        result = Matrix(a.rows, a.cols)
        for r in range(a.rows):
            for c in range(a.cols):
                result.data[r][c] = a.data[r][c] - b.data[r][c]
        return result        
        
def Transpose(matrix):
        return Map(Matrix(matrix.cols, matrix.rows),lambda e,r,c: matrix.data[c][r]) 
    
def Multiply(a, b):
    #Matrix product
    if (a.cols != b.rows):
        print('Columns of A must match rows of B.')
        return
    else:
        result = Matrix(a.rows,b.cols)
        for r in range(result.rows):
            for c in range(result.cols):
                sum = 0
                for k in range(a.cols):
                    sum += a.data[r][k] * b.data[k][c]
                result.data[r][c] = sum
        return result    
        
def Map(matrix, func):
    return Matrix(matrix.rows, matrix.cols).Map(lambda e,r,c: func(matrix.data[r][c], r, c))
    
