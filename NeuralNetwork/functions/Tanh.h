//
//  Tanh.h
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/15/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef Tanh_h
#define Tanh_h

#include <stdio.h>
#include "TransferFunction.h"

class Tanh : public TransferFunction {
public:
	
	Tanh();
	virtual ~Tanh();
	
	double getOutput(double x);
	double getDerivative(double x);
	
	
};

#endif /* Tanh_h */
