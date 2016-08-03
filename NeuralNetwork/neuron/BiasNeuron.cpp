/*
 * BiasNeuron.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "BiasNeuron.h"

BiasNeuron::BiasNeuron(std::string id) : Neuron(id) {
	// TODO Auto-generated constructor stub
	this->setInput(1.0f);

}

BiasNeuron::~BiasNeuron() {
	// TODO Auto-generated destructor stub
}

double BiasNeuron::getOutput() {
	return 1;
}

void BiasNeuron::calculate() {

}

