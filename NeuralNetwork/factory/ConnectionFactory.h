/*
 * ConnectionFactory.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef CONNECTIONFACTORY_H_
#define CONNECTIONFACTORY_H_

#include "Connection.h"
#include "Neuron.h"
#include "NeuronLayer.h"

class ConnectionFactory {
public:
	ConnectionFactory();
	virtual ~ConnectionFactory();

	static Connection *createConnection(Neuron *fromNeuron, Neuron *toNeuron);
	static void fullConection(NeuronLayer *fromLayer, NeuronLayer *toLayer);

};

#endif /* CONNECTIONFACTORY_H_ */
