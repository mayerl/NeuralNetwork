/*
 * InputNeuron.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "InputNeuron.h"

InputNeuron::InputNeuron(std::string id) : Neuron(id) {
	// TODO Auto-generated constructor stub

}

InputNeuron::~InputNeuron() {
	// TODO Auto-generated destructor stub
}

void InputNeuron::calculate() {
	this->output = this->netInput;
}
