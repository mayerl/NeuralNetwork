/*
 * Connection.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "Connection.h"
#include <random>

Connection::Connection(Neuron *fromNeuron, Neuron *toNeuron) {
	this->fromNeuron = fromNeuron;
	this->toNeuron = toNeuron;
	this->weight = rngMin + (rngMax - rngMin) * ((double)rand() / (double)RAND_MAX);
	this->delta = 0.0f;
}

Connection::Connection(Neuron *fromNeuron, Neuron *toNeuron, double weight) {
	this->fromNeuron = fromNeuron;
	this->toNeuron = toNeuron;
	this->weight = weight;
	this->delta = 0.0f;
}

double Connection::getWeight() {
	return this->weight;
}

void Connection::setWeight(double x) {
	this->weight = x;
}

double Connection::getDelta() {
	return this->delta;
}

void Connection::setDelta(double x) {
	this->delta = x;
}

double Connection::getSummedDelta() {
	return this->summedDelta;
}

void Connection::setSummedDelta(double x) {
	this->summedDelta = x;
}

Connection::~Connection() {
	// TODO Auto-generated destructor stub
}

