//
//  Tanh.cpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/15/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include "Tanh.h"
#include <cmath>

Tanh::Tanh() {
	this->type = TANH;
}

Tanh::~Tanh() {
	// TODO Auto-generated destructor stub
}

double Tanh::getOutput(double x) {
	return tanh(x);
}

double Tanh::getDerivative(double x) {
	double fx = getOutput(x);
	return 1 - (fx * fx);
}