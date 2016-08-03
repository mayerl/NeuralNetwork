/*
 * WeightedSum.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "WeightedSum.h"
#include "Neuron.h"

WeightedSum::WeightedSum() {
	// TODO Auto-generated constructor stub

}

WeightedSum::~WeightedSum() {
	// TODO Auto-generated destructor stub
}

double WeightedSum::getOutput(std::vector<Connection*> inputConnections) {
	double out = 0.0;
	for (Connection *conn : inputConnections) {
		out += conn->getWeight() * conn->fromNeuron->getOutput();
	}
	return out;
}


