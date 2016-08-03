//
//  QuadraticErrorFunction.cpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/10/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include "QuadraticCostFunction.h"
#include <math.h>

QuadraticCostFunction::QuadraticCostFunction() {
	
	this->type = QUADRATIC;
	this->name = "MSE";
	
}

QuadraticCostFunction::~QuadraticCostFunction() {
	
	
}

double QuadraticCostFunction::getCost(double output, double target) {
	
	return (target - output) * (target - output) * 0.5;
	
}

double QuadraticCostFunction::getGradient(double output, double target) {
	
	return (target - output);
	
}

double QuadraticCostFunction::getMeanCost(double summedCost, int samples) {
	
	return summedCost / samples;
	
}