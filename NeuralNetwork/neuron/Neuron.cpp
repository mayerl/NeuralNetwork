/*
 * Neuron.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "Neuron.h"
#include "Sigmoid.h"
#include "WeightedSum.h"
#include "BiasNeuron.h"

Neuron::Neuron(std::string id) {

	this->id = id;
	this->transferFunction = new Sigmoid();
	this->inputFunction = new WeightedSum();

}

void Neuron::addInputConnection(Connection *conn) {
	inputConnections.push_back(conn);
}

void Neuron::addOutputConnection(Connection *conn) {
	outputConnections.push_back(conn);
}

std::vector<Connection*> Neuron::getInputConnections() {
	return inputConnections;
}

std::vector<Connection*> Neuron::getOutputConnections() {
	return outputConnections;
}

void Neuron::calculate() {
	
	if ((this->inputConnections.size() > 0)) {
		this->setInput(this->inputFunction->getOutput(this->getInputConnections()));
		output = this->transferFunction->getOutput(this->getNetInput());
	} else {
		output = this->getNetInput();
	}
	
}

double Neuron::getOutput() {
	return output;
}

double Neuron::getNetInput() {
	return netInput;
}

void Neuron::setInput(double x) {
	this->netInput = x;
}

void Neuron::setOutput(double x) {
	this->output = x;
}

double Neuron::getError() {
	return this->error;
}

void Neuron::setError(double x) {
	this->error = x;
}

TransferFunction* Neuron::getTransferFunction() {
	return this->transferFunction;
}

void Neuron::setTransferFunction(TransferFunction *func) {
	this->transferFunction = func;
}

void Neuron::updateNetInput() {
	if ((this->inputConnections.size() > 0)) {
		this->setInput(this->inputFunction->getOutput(this->getInputConnections()));
	}
}

Neuron::~Neuron() {
	// TODO Auto-generated destructor stub
}

