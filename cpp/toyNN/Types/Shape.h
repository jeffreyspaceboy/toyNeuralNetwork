//
//  Shape.h
//  toyNN
//
//  Created by Jeffrey Fisher on 7/19/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Shape_h
#define Shape_h

#include <vector>

class Shape{
    public:
        //---Constructors---//
        Shape();    
        Shape(unsigned int x_size);
        Shape(unsigned int x_size, unsigned int y_size);
        Shape(unsigned int x_size, unsigned int y_size, unsigned int z_size);
        //---Copy Constructors---//
        Shape(const Shape &obj);
        //---Destructors---//
        ~Shape(void);
        
        //---Vars--//
        unsigned int size;
        std::vector<unsigned int> dim; //Dimentions of Tensor Size
};
#endif /* Shape_h */
