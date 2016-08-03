/*
 * Sigmoid.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "Sigmoid.h"
#include <cmath>

Sigmoid::Sigmoid() {
	
	this->type = SIGMOID;

}

Sigmoid::~Sigmoid() {
	// TODO Auto-generated destructor stub
}

double Sigmoid::getOutput(double x) {
	return 1 / (1 + exp(-x));
}

double Sigmoid::getDerivative(double x) {
	double fx = getOutput(x);
	return fx * (1 - fx);
}

