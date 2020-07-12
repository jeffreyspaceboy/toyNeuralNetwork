//
//  Cell.hpp
//  toyNN
//
//  Created by Jeffrey Fisher on 7/12/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>

class Cell{
    public:
        unsigned int d[3] = {0,0,0};
    
        //---Constructors---//
        Cell();
        Cell(const unsigned int x, const unsigned int y);
        Cell(const unsigned int x, const unsigned int y, const unsigned int z);
        //---Copy Constructors---//
        Cell(const Cell &obj);
        //---Destructors---//
        ~Cell();
    
        //---Get---//
        unsigned int z();
        unsigned int y();
        unsigned int x();
    
        //---Set---//
        void z(unsigned int z);
        void y(unsigned int y);
        void x(unsigned int x);
    
        //---Other---//
        void print();
};


#endif /* Cell_hpp */
