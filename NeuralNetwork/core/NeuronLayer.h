/*
 * NeuronLayer.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef NEURONLAYER_H_
#define NEURONLAYER_H_

#include <vector>
#include "Neuron.h"

typedef std::vector<std::unique_ptr<Neuron>> NeuronVector;

class NeuronLayer {
public:
	NeuronLayer();
	virtual ~NeuronLayer();
	NeuronLayer(int lid, int n_neurons, TransferFunction * transferFunc, bool addBias);
	NeuronLayer(int lid, int n_neurons, TransferFunction * transferFunc);
	std::vector<Neuron*> getNeurons();
	int getSize();
	void calculate();

	std::vector<Neuron*> neurons;
};

#endif /* NEURONLAYER_H_ */
