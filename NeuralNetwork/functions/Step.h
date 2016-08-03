/*
 * Step.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef STEP_H_
#define STEP_H_

#include "TransferFunction.h"

class Step : public TransferFunction {
public:
	Step();
	virtual ~Step();

	double getOutput(double x);
	double getDerivative(double x);
	
};

#endif /* STEP_H_ */
