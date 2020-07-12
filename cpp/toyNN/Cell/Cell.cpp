//
//  Cell.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 7/12/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Cell.hpp"

//---Constructors---//
Cell::Cell(){}

Cell::Cell(const unsigned int x, const unsigned int y){
    this->d[1] = y;
    this->d[0] = x;
}

Cell::Cell(const unsigned int x, const unsigned int y, const unsigned int z){
    this->d[2] = z;
    this->d[1] = y;
    this->d[0] = x;
}

//---Copy Constructors---//
Cell::Cell(const Cell &obj){
    this->d[2] = obj.d[2];
    this->d[1] = obj.d[1];
    this->d[0] = obj.d[0];
}

//---Destructors---//
Cell::~Cell(){}

unsigned int Cell::z(){ return this->d[2]; }
unsigned int Cell::y(){ return this->d[1]; }
unsigned int Cell::x(){ return this->d[0]; }

void Cell::z(unsigned int z){ this->d[2] = z; }
void Cell::y(unsigned int y){ this->d[1] = y; }
void Cell::x(unsigned int x){ this->d[0] = x; }

//---Other---//
void Cell::print(){
    printf("[z,y,x] = [%d,%d,%d]\n",this->d[2],this->d[1],this->d[0]);
}
