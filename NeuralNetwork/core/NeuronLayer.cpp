/*
 * NeuronLayer.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "NeuronLayer.h"
#include "Neuron.h"
#include "BiasNeuron.h"
#include "Softmax.h"
#include <sstream>
#include <iostream>

NeuronLayer::NeuronLayer(int lid, int n_neurons, TransferFunction * transferFunc, bool addBias) {

	int n = 0;
	
	if (addBias) {
		std::stringstream sstm;
		sstm << lid << "#" << n++;
		BiasNeuron *neuron = new BiasNeuron(sstm.str());
		neuron->setTransferFunction(transferFunc);
		this->neurons.push_back(neuron);
	}

	for (int i = 0; i < n_neurons; i++) {
		try {
			std::stringstream sstm;
			sstm << lid << "#" << n++;
			Neuron *neuron = new Neuron(sstm.str());
			neuron->setTransferFunction(transferFunc);
			this->neurons.push_back(neuron);
		} catch (const std::exception &e) {
            std::cerr << e.what();
		}
	}
	
	if (dynamic_cast<Softmax*>(transferFunc)) {
		((Softmax*)transferFunc)->setOutputLayer(this);
	}

}

NeuronLayer::NeuronLayer(int id, int n_neurons, TransferFunction * transferFunc) : NeuronLayer(id, n_neurons, transferFunc, true) {

}

std::vector<Neuron*> NeuronLayer::getNeurons() {
	return neurons;
}

int NeuronLayer::getSize() {
	return (int)this->neurons.size();
}

void NeuronLayer::calculate() {
	for (Neuron *neuron : neurons) {
		neuron->updateNetInput();
	}
	
	for (Neuron *neuron : neurons) {
		neuron->calculate();
	}
}

NeuronLayer::~NeuronLayer() {
	// TODO Auto-generated destructor stub
}

