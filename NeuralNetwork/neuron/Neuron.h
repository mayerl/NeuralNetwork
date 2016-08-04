/*
 * Neuron.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef NEURON_H_
#define NEURON_H_

#include <string>
#include <vector>
#include "../functions/TransferFunction.h"
#include "../functions/InputFunction.h"

class Connection;
class InputFunction;

class Neuron {
public:
	
	std::string id;
	
	Neuron(std::string id);
	virtual ~Neuron();

	void addInputConnection(Connection *conn);
	void addOutputConnection(Connection *conn);
	std::vector<Connection*> getInputConnections();
	std::vector<Connection*> getOutputConnections();
	virtual void calculate();
	virtual double getOutput();
	double getNetInput();
	void setInput(double x);
	void setOutput(double x);
	double getError();
	void setError(double x);
	TransferFunction *getTransferFunction();
	void setTransferFunction(TransferFunction *func);
	void updateNetInput();

protected:
	double netInput;
	double output;
	double error;
	TransferFunction *transferFunction;
	InputFunction *inputFunction;
	std::vector<Connection*> inputConnections;
	std::vector<Connection*> outputConnections;
};

#endif /* NEURON_H_ */
