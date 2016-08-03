/*
 * BiasNeuron.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef BIASNEURON_H_
#define BIASNEURON_H_

#include "Neuron.h"

class BiasNeuron : public Neuron {
public:
	BiasNeuron(std::string id);
	virtual ~BiasNeuron();

	double getOutput();
	void calculate();
};

#endif /* BIASNEURON_H_ */
