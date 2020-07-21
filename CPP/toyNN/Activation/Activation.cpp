//
//  Activation.cpp
//  toyNN
//
//  Created by Jeffrey Fisher on 7/12/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#include "Activation.h"

float singleSigmoid(float val, Cell cell){
    return (1/(1+(exp(-val))));
}

float singleDSigmoid(float val, Cell cell){
    return (singleSigmoid(val, cell)*(1-singleSigmoid(val, cell)));
}
