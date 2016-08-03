//
//  Softmax.cpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 6/16/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include "Softmax.h"
#include <cmath>

Softmax::Softmax() {
	this->type = SOFTMAX;
}

Softmax::~Softmax() {
	// TODO Auto-generated destructor stub
}

double Softmax::getOutput(double x) {
	double result = 0.0f;
	if (outputLayer != 0) {
		for (Neuron *neuron : outputLayer->getNeurons()) {
			result += exp(neuron->getNetInput());
		}
		result = exp(x) / result;
	} else {
		throw new std::exception();
	}
	return result;
}

double Softmax::getDerivative(double x) {
	double fx = getOutput(x);
	return fx * (1 - fx);
}

void Softmax::setOutputLayer(NeuronLayer *outputLayer) {
	this->outputLayer = outputLayer;
}

