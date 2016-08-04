/*
 * TransferFunction.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef TRANSFERFUNCTION_H_
#define TRANSFERFUNCTION_H_

#include <vector>
#include "../json/json.h"

typedef enum {STEP, SIGMOID, TANH, SOFTMAX} transferFuncTypes;

class NeuronLayer;
class Neuron;

class TransferFunction {
public:
	TransferFunction();
	virtual ~TransferFunction();

	virtual double getOutput(double x);
	virtual double getDerivative(double x);
	Json::Value generateJson();
	
protected:
	double output;
	transferFuncTypes type;
};

#endif /* TRANSFERFUNCTION_H_ */
