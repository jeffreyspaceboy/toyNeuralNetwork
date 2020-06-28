//
//  Tensor.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 6/2/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Tensor.hpp"

//---Constructors---//
Tensor::Tensor(double ***input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size, std::string name){
    this->set_data(input_data, x_size, y_size, z_size);
    this->name = name;
}

Tensor::Tensor(double *input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size, std::string name){
    this->set_data(input_data, x_size, y_size, z_size);
    this->name = name;
}

Tensor::Tensor(unsigned int x_size, unsigned int y_size, unsigned int z_size){
    double ***input_data = NULL;
    this->set_data(input_data, x_size, y_size, z_size);
}


Tensor::Tensor(){} //Standard Constructor

//---Copy Constructors---//
Tensor::Tensor(const Tensor &obj){ this->copy_data(obj); } //Copy constructor

//---Destructors---//
Tensor::~Tensor(void){
    if(this->data != NULL){
        unsigned int y,z;
        for(z = 0; z < this->z_size; z++) {
            for(y = 0; y < this->y_size; y++) {
                free(this->data[z][y]);
            }
            free(this->data[z]);
        }
        free(this->data);
    }
}

inline std::string Tensor::get_name(){ return this->name; }
inline unsigned int Tensor::get_x_size(){ return this->x_size; }
inline unsigned int Tensor::get_y_size(){ return this->y_size; }
inline unsigned int Tensor::get_z_size(){ return this->z_size;}
inline double *** Tensor::get_data(){ return this->data; }

void Tensor::zero(){
    if(this->data == NULL){
        unsigned int x,y,z;
        this->data = (double ***) malloc(this->z_size * sizeof(double**));
        for(z = 0; z < this->z_size; z++) {
            this->data[z] = (double **) malloc(this->y_size * sizeof(double *));
            for(y = 0; y < this->y_size; y++) {
                this->data[z][y] = (double *) malloc(this->x_size * sizeof(double));
                for(x = 0; x < this->x_size; x++){
                    this->data[z][y][x] = 0.0;
                }
            }
        }
    }else{
        unsigned int x,y,z;
        for(z = 0; z < this->z_size; z++) {
            for(y = 0; y < this->y_size; y++) {
                for(x = 0; x < this->x_size; x++){
                    this->data[z][y][x] = 0.0;
                }
            }
        }
    }
}


void Tensor::set_name(std::string new_name){ this->name = new_name; }
void Tensor::set_element(double val, unsigned int x, unsigned int y, unsigned int z){ this->data[z][y][x] = val; }

void Tensor::set_data(double ***input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size){
    this->x_size = x_size;
    this->y_size = y_size;
    this->z_size = z_size;
    if(input_data == NULL){
        zero();
    }else{
        this->data = input_data;
    }
}

void Tensor::set_data(double *input_data, unsigned int x_size, unsigned int y_size, unsigned int z_size){
    this->x_size = x_size;
    this->y_size = y_size;
    this->z_size = z_size;
    if(input_data == NULL){
        zero();
    }else{
        unsigned int x,y,z;
        if(this->data == NULL){
            this->data = (double ***) malloc(this->z_size * sizeof(double**));
            for(z = 0; z < this->z_size; z++) {
                this->data[z] = (double **) malloc(this->y_size * sizeof(double *));
                for(y = 0; y < this->y_size; y++) {
                    this->data[z][y] = (double *) malloc(this->x_size * sizeof(double));
                    for(x = 0; x < this->x_size; x++){
                        this->data[z][y][x] = input_data[x + y*this->x_size + z*this->y_size*this->x_size];
                    }
                }
            }
        }else{
            unsigned int x,y,z;
            for(z = 0; z < this->z_size; z++) {
                for(y = 0; y < this->y_size; y++) {
                    for(x = 0; x < this->x_size; x++){
                        this->data[z][y][x] = input_data[x + y*this->x_size + z*this->y_size*this->x_size];
                    }
                }
            }
        }
    }
}

void Tensor::copy_data(const Tensor &sampleTensor){
    this->x_size = sampleTensor.x_size;
    this->y_size = sampleTensor.y_size;
    this->z_size = sampleTensor.z_size;
    this->data = (double ***) malloc(this->z_size * sizeof(double**));
    unsigned int x,y,z;
    for(z = 0; z < this->z_size; z++) {
        this->data[z] = (double **) malloc(this->y_size * sizeof(double *));
        for(y = 0; y < this->y_size; y++) {
            this->data[z][y] = (double *) malloc(this->x_size * sizeof(double));
        }
    }
    for(z = 0; z < this->z_size; z++) {
        for(y = 0; y < this->y_size; y++) {
            for(x = 0; x < this->x_size; x++){
                this->data[z][y][x] = sampleTensor.data[z][y][x];
            }
        }
    }
}

//---Math Operations---//
void Tensor::map(double func(double val, unsigned int x, unsigned int y, unsigned int z)){
    unsigned int x,y,z;
    for(z = 0; z < this->z_size; z++) {
        for(y = 0; y < this->y_size; y++) {
            for(x = 0; x < this->x_size; x++){
                double val = this->data[z][y][x];
                this->data[z][y][x] = (*func)(val,x,y,z);
            }
        }
    }
}

Tensor Tensor::map(const Tensor &obj, double func(double val, unsigned int x, unsigned int y, unsigned int z)){
    Tensor newTensor(obj);
    newTensor.map(func);
    return newTensor;
}

Tensor Tensor::operator +(const Tensor &obj){ //Overloading add operator
    if((this->get_x_size() != obj.x_size) || (this->get_y_size() != obj.y_size) || (this->get_z_size() != obj.z_size)){ //Check matrix dimensions.
        printf("ERROR: Dimensions must match.\n");
        exit(1);
    } //If tensor dimensions match, then do add.
    Tensor newTensor(*this);
    unsigned int x,y,z;
    for(z = 0; z < this->z_size; z++) {
        for(y = 0; y < this->y_size; y++) {
            for(x = 0; x < this->x_size; x++){
                newTensor.data[z][y][x] = this->data[z][y][x] + obj.data[z][y][x];
            }
        }
    }
    return newTensor;
    
}

Tensor Tensor::operator -(const Tensor &obj){ //Overloading subtract operator
    if((this->get_x_size() != obj.x_size) || (this->get_y_size() != obj.y_size) || (this->get_z_size() != obj.z_size)){ //Check matrix dimensions.
        printf("ERROR: Dimensions must match.\n");
        exit(1);
    }//If tensor dimensions match, then do add.
    Tensor newTensor(*this);
    unsigned int x,y,z;
    for(z = 0; z < this->z_size; z++) {
        for(y = 0; y < this->y_size; y++) {
            for(x = 0; x < this->x_size; x++){
                newTensor.data[z][y][x] = this->data[z][y][x] - obj.data[z][y][x];
            }
        }
    }
    return newTensor;
}

Tensor Tensor::operator *(const Tensor &obj){ //Overloading subtract operator
    if((this->get_x_size() != obj.x_size) || (this->get_y_size() != obj.y_size) || (this->get_z_size() != obj.z_size)){ //Check matrix dimensions.
        printf("ERROR: Dimensions must match.\n");
        exit(1);
    }//If tensor dimensions match, then do add.
    Tensor newTensor(*this);
    unsigned int x,y,z;
    for(z = 0; z < this->z_size; z++) {
        for(y = 0; y < this->y_size; y++) {
            for(x = 0; x < this->x_size; x++){
                newTensor.data[z][y][x] = this->data[z][y][x] * obj.data[z][y][x];
            }
        }
    }
    return newTensor;
}

Tensor Tensor::operator ->*(const Tensor &obj){ //CROSS PRODUCT - overloading the ->* operator
    if(this->x_size != obj.y_size){ //For cross product the cols of mat 1 and rows of mat 2 must be equal.
        std::cout<<"ERROR: Columns of A must match rows of B."<<std::endl;
        exit(1);
    }
    if(this->z_size != obj.z_size){ //Tensors must be of the same layer height
        std::cout<<"ERROR: Tensor number of layers must be consistant."<<std::endl;
        exit(1);
    }
    Tensor result(obj.x_size, this->y_size, this->z_size);
    unsigned int z,w,y,x;
    for(z = 0; z < this->z_size; z++){
        for(y = 0; y < result.y_size; y++){
            for(x = 0; x < result.x_size; x++){
                for(w = 0; w < this->x_size; w++){
                    result.data[z][y][x] += this->data[z][y][w] * obj.data[z][w][x];//Preforming matrix product
                }
            }
        }
    }
    return result;
}




void Tensor::print(){
    unsigned int x,y,z;
    printf("%s::{\n",this->name.c_str());
    for(z = 0; z < this->z_size; z++) {
        printf("Layer: %d\n", z);
        for(y = 0; y < this->y_size; y++) {
            printf("[");
            for(x = 0; x < this->x_size-1; x++){
                printf("%f,",this->data[z][y][x]);
            }
            printf("%f]\n",this->data[z][y][this->x_size-1]);
        }
    }
    printf("}::%s\n",this->name.c_str());
}

