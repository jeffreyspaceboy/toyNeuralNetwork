//
//  Shape.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 7/11/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Shape.hpp"

//---Constructors---//
Shape::Shape(){}

Shape::Shape(const unsigned int x_size, const unsigned int y_size){
    this->size = y_size * x_size;
    this->d[1] = y_size;
    this->d[0] = x_size;
}

Shape::Shape(const unsigned int x_size, const unsigned int y_size, const unsigned int z_size){
    this->size = z_size * y_size * x_size;
    this->d[2] = z_size;
    this->d[1] = y_size;
    this->d[0] = x_size;
}

//---Copy Constructors---//
Shape::Shape(const Shape &obj){
    this->size = obj.size;
    this->d[2] = obj.d[2];
    this->d[1] = obj.d[1];
    this->d[0] = obj.d[0];
}

//---Destructors---//
Shape::~Shape(){}

unsigned int Shape::z_size(){ return this->d[2]; }
unsigned int Shape::y_size(){ return this->d[1]; }
unsigned int Shape::x_size(){ return this->d[0]; }

//---Other---//
void Shape::print(){
    printf("[z,y,x] = [%d,%d,%d]\n",this->d[2],this->d[1],this->d[0]);
}
