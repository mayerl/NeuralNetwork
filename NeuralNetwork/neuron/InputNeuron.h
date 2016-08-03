/*
 * InputNeuron.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef INPUTNEURON_H_
#define INPUTNEURON_H_

#include "Neuron.h"

class InputNeuron : public Neuron {
public:
	InputNeuron(std::string id);
	virtual ~InputNeuron();

	void calculate();
};

#endif /* INPUTNEURON_H_ */
