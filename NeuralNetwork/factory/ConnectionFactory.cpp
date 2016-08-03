/*
 * ConnectionFactory.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "ConnectionFactory.h"
#include "BiasNeuron.h"

ConnectionFactory::ConnectionFactory() {
	// TODO Auto-generated constructor stub

}

Connection *ConnectionFactory::createConnection(Neuron *fromNeuron, Neuron *toNeuron) {
		return new Connection(fromNeuron, toNeuron);
}

void ConnectionFactory::fullConection(NeuronLayer *fromLayer, NeuronLayer *toLayer) {
	
    for(Neuron *fromNeuron : fromLayer->getNeurons()) {
        for (Neuron *toNeuron : toLayer->getNeurons()) {
				if (!dynamic_cast<BiasNeuron*>(toNeuron)) {
					Connection *conn = createConnection(fromNeuron, toNeuron);
					toNeuron->addInputConnection(conn);
					fromNeuron->addOutputConnection(conn);
				}
			}
		}

}

ConnectionFactory::~ConnectionFactory() {
	// TODO Auto-generated destructor stub
}

