//
//  CrossEntropyCostFunction.cpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/10/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include "CrossEntropyCostFunction.h"
#include <math.h>

CrossEntropyCostFunction::CrossEntropyCostFunction() {
	
	this->type = CROSS_ENTROPY;
	this->name = "CE";
	
}

CrossEntropyCostFunction::~CrossEntropyCostFunction() {
	
}

double CrossEntropyCostFunction::getCost(double output, double target) {
	
	return - target * log(output) - (1 - target) * log(1 - output);
	
}

double CrossEntropyCostFunction::getGradient(double output, double target) {
	
	return (target - output) / ( (1 - output) * output );
	
}

double CrossEntropyCostFunction::getMeanCost(double summedCost, int samples) {
	
	return summedCost / samples;
	
}