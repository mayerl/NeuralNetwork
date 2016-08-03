/*
 * Connection.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

class Neuron;

class Connection {
public:
	Connection();
	virtual ~Connection();

	Neuron *fromNeuron;
	Neuron *toNeuron;

	Connection(Neuron *fromNeuron, Neuron *toNeuron);
	Connection(Neuron *fromNeuron, Neuron *toNeuron, double weight);
	double getWeight();
	void setWeight(double x);
	double getDelta();
	void setDelta(double x);
	double getSummedDelta();
	void setSummedDelta(double x);

private:

	double weight;
	double delta = 0.0;
	double summedDelta = 0.0;
	double rngMin = -0.05;
	double rngMax = 0.05;
};

#endif /* CONNECTION_H_ */
