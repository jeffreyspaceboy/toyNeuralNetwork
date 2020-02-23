xEdgeKernal = [[-1,-1,-1],
               [-1,8,-1],
               [-1,-1,-1]]

class Image:
    def __init__(self, fileName): #Pixel Ratio: num of original pixels / 1 new pixel
        self.fileName = fileName;
        self.img = loadImage(fileName);
        self.imageArray = self.toArray();
    def show(self):
        image(self.img,0,0);
    def toArray(self):
        newArray = [];
        self.img.loadPixels();
        for y in range(height):
            for x in range(width):
                loc = x + y*width;
                newArray.append(self.img.pixels[loc]);
        return newArray; 
        
    def applyKernal(self,kernalArray):
        matrixSize = len(kernalArray);
        self.img.loadPixels();
        for y in range(height):
            for x in range(width):
                rTotal = 0;
                gTotal = 0;
                bTotal = 0;
                for i in range(matrixSize):
                    for j in range(matrixSize):
                        xloc = x+i
                        yloc = y+j
                        loc = xloc + width*yloc
                        loc = constrain(loc,0,len(self.img.pixels)-1)
                        rTotal += (red(self.img.pixels[loc]) * kernalArray[i][j])
                        gTotal += (green(self.img.pixels[loc]) * kernalArray[i][j])
                        bTotal += (blue(self.img.pixels[loc]) * kernalArray[i][j])
                rTotal = constrain(rTotal,0,255)
                gTotal = constrain(gTotal,0,255)
                bTotal = constrain(bTotal,0,255)
                c = color(rTotal,gTotal,bTotal)
                loc = x + y*width;
                self.img.pixels[loc] = c
        self.img.updatePixels();
