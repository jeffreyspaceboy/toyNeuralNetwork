//
//  Activation.h
//  toyNN
//
//  Created by Jeffrey Fisher on 7/12/20.
//  Copyright © 2020 Jeffrey Fisher. All rights reserved.
//

#ifndef Activation_h
#define Activation_h

#include <stdio.h>
#include <math.h>

#include "Cell.h"

float singleSigmoid(float val, Cell cell);
float singleDSigmoid(float val, Cell cell);

#endif /* Activation_h */
