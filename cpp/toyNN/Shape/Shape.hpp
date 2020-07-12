//
//  Shape.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 7/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>

class Shape{
    public:
        unsigned int d[3] = {0,0,0};
        unsigned int size = 0;
    
        //---Constructors---//
        Shape();
        Shape(const unsigned int x_size, const unsigned int y_size);
        Shape(const unsigned int x_size, const unsigned int y_size, const unsigned int z_size);
        //---Copy Constructors---//
        Shape(const Shape &obj);
        //---Destructors---//
        ~Shape();
    
        //---Get---//
        unsigned int z_size();
        unsigned int y_size();
        unsigned int x_size();
    
        //---Other---//
        void print();

        
};

#endif /* Shape_hpp */
