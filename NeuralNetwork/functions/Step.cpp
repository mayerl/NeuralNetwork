/*
 * Step.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "Step.h"

Step::Step() {
	
	this->type = STEP;

}

Step::~Step() {
	// TODO Auto-generated destructor stub
}

double Step::getOutput(double x) {
	return (x >= 0) ? 0.99 : 0.01;
}

double Step::getDerivative(double x) {
	return 1;
}
