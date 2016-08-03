/*
 * Sigmoid.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef SIGMOID_H_
#define SIGMOID_H_

#include "TransferFunction.h"

class Sigmoid : public TransferFunction {
public:
	Sigmoid();
	virtual ~Sigmoid();

	double getOutput(double x);
	double getDerivative(double x);

};

#endif /* SIGMOID_H_ */
