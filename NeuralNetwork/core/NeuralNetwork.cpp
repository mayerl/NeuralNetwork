/*
 * NeuralNetwork.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "NeuralNetwork.h"
#include "../neuron/InputNeuron.h"
#include "NeuronLayer.h"
#include "../functions/Step.h"
#include "../functions/Sigmoid.h"
#include "../core/ConnectionFactory.h"
#include "../functions//CostFunction.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <cfloat>

using namespace std;

NeuralNetwork::NeuralNetwork(int n_inputs, int n_outputs) {

	NeuralNetwork(n_inputs, n_outputs, new NeuralNetworkProperties());

}

NeuralNetwork::NeuralNetwork(int n_inputs, int n_outputs, NeuralNetworkProperties *properties) {

	this->n_inputs = n_inputs;
	this->n_outputs = n_outputs;
	this->properties = properties;
	
	this->dataSet = NULL;
	this->trainingData = NULL;
	this->testingData = NULL;
	
	createLayers();

}

NeuralNetwork::NeuralNetwork(Json::Value json) : NeuralNetwork(json["n_inputs"].asInt(), json["n_outputs"].asInt(), new NeuralNetworkProperties(json["properties"])) {
	
	this->trained = json["trained"].asBool();
	
	Json::Value jWeights = json["weights"];
	
	for (int l = 0; l < this->layers.size(); l++) {
		NeuronLayer *layer = this->layers.at(l);
		Json::Value jLayer = json["weights"][l];
		int k = 0;
		for (Neuron *neuron : layer->getNeurons()) {
			for (Connection *conn : neuron->getOutputConnections()) {
				
				conn->setWeight(jLayer[k++].asDouble());
				
			}
		}
	}
	
	this->setDataSet(new DataSet(json["dataSet"]));
	this->divideDataSet();
	
}

void NeuralNetwork::createLayers() {
	
	int n_hiddenLayers = properties->n_hiddenLayers;
	int n_hiddenNeurons = (properties->n_hiddenNeurons == 0) ? this->n_inputs * 2 : properties->n_hiddenNeurons;
	
	// Create input layer
	NeuronLayer *in = new NeuronLayer(0, n_inputs, properties->hiddenTransferFunction, true);
	
	layers.push_back(in);
	
	// Create all hidden layers
	for (int i = 0; i < n_hiddenLayers; i++) {
		NeuronLayer *hi = new NeuronLayer(i + 1, n_hiddenNeurons,properties->hiddenTransferFunction);
		layers.push_back(hi);
	}
	
	// Create output layer
	NeuronLayer *out = new NeuronLayer(n_hiddenLayers + 1, n_outputs, properties->outputTransferFunction, false);
	
	layers.push_back(out);
	
	// Connect all neurons
	for (int i = 1; i < layers.size(); i++) {
		ConnectionFactory::fullConection(layers.at(i-1), layers.at(i));
	}
	
}

void NeuralNetwork::setDataSet(DataSet* data) {
	
	dataSet = data;
	std::random_shuffle(dataSet->data.begin(), dataSet->data.end());
	divideDataSet();
	
}

void NeuralNetwork::divideDataSet() {
	
	// Divide the dataset into training and testing sets
	this->trainingData = new DataSet(n_inputs, n_outputs);
	this->testingData = new DataSet(n_inputs, n_outputs);
	
	int n_train = this->dataSet->data.size() * this->properties->trainingProportion;
	
	for (int i = 0; i < n_train; i++) {
		
		this->trainingData->data.push_back(this->dataSet->data.at(i));
		
	}
	
	for (int i = n_train; i < this->dataSet->data.size(); i++) {
		
		this->testingData->data.push_back(this->dataSet->data.at(i));
		
	}
	
}

void NeuralNetwork::setTrainingData(DataSet *data) {
	
	this->trainingData = data;
	
}

void NeuralNetwork::setTestingData(DataSet *data) {
	
	this->testingData = data;
	
}

DataSet *NeuralNetwork::getDataSet() {
	
	return this->dataSet;
	
}

DataSet *NeuralNetwork::getTrainingData() {
	
	return this->trainingData;
	
}

DataSet *NeuralNetwork::getTestingData() {
	
	return this->testingData;
	
}

int NeuralNetwork::getNumberInputs() {
	return this->n_inputs;
}
int NeuralNetwork::getNumberOutputs() {
	return this->n_outputs;
}

std::vector<double> NeuralNetwork::run(std::vector<double> in, bool verbose) {

	// Set the inputs of the input layers
	for (int i = 0; i < in.size(); i++) {
		layers.at(0)->getNeurons()[i+1]->setInput(in[i]);
	}
    std::vector<double> outputs;

	// For each layer (and neuron) calculate the outputs
	for (NeuronLayer *layer : layers) {
		layer->calculate();
	}

	// Update the results vector with the outputs
    for (Neuron *neuron : layers.at(layers.size()-1)->getNeurons()) {
		outputs.push_back(neuron->getOutput());
	}
    
    if (verbose) {

		std::cout << "Inputs: ";
    
		for (double i : in) {
			std::cout << i << ", ";
		}
    
		std::cout << endl << "Outputs: ";
    
		for (double o : outputs) {
			std::cout << o << ", ";
		}
    
		std:cout << endl;
        
    }

	return outputs;

}

void NeuralNetwork::train() throw() {
	
	if (this->trainingData == NULL) {
        cout << "Training data set not found!" << endl;
		throw new std::exception();
	}

	if (properties->verbose) cout << "Starting training..." << endl;

    double totalError = DBL_MAX;
    int errorCount = 1;
    double errorRate = 1;
    double output = 0;
    double target = 0;
    int epoch = 0;
    long startTime = time(0);
	
	vector<double> bestWeights;
	int bestEpoch = 0;
	double bestError = DBL_MAX;

	// Stop training only if we hit min error or max number of iterations
    while(totalError > properties->minErrorRate && epoch < properties->maxIte) {

		if (this->signal_abort) break;
		
		// Shuffle the training set each epoch to prevent over fitting training
		std::random_shuffle(trainingData->data.begin(), trainingData->data.end());

    	errorCount = 0;
    	totalError = 0;

		// For each training set, run a step of the back-propagation algorithm
    	for (int u = 0; u < trainingData->data.size(); u++) {

			// Run the network for this pattern's inputs
    		this->run(trainingData->data.at(u)->inputs, false);

			double neuronErr = 0;
			double cost = 0;
			double patternError = 0;
			
			// Iterate through all neurons and update the weights
    		for (int k = (int)layers.size() - 1; k > 0; k--) {

    			NeuronLayer *layer = layers.at(k);

				int out_n = 0;
        		for (Neuron *neuron : layer->getNeurons()) {
					
					neuronErr = 0;

					// Is this the output layer?
					if (k == layers.size() - 1) {
						
						// For output layer, the error gradient is the derivate of the costFunction.
						output = neuron->getOutput();
						target = trainingData->data.at(u)->outputs[out_n++];
						
						cost = properties->costFunction->getCost(output, target);
						totalError += cost;
						patternError += cost;
						
						// neuronErr is the error gradient
						neuronErr = properties->costFunction->getGradient(output, target);
						
					} else {
						
						// For hidden layer, the error gradient is the sum of the δ of neurons this one connects to, multuplied by their correspondent weight.
						for (Connection *outConn : neuron->getOutputConnections()) {
							// δi = Σδj * wj
							neuronErr += outConn->toNeuron->getError() * outConn->getWeight();

						}
						
					}

					// Multiply the error gradient by the transfer function derivate to get δ
        			neuronErr *= neuron->getTransferFunction()->getDerivative(neuron->getNetInput());
					
        			neuron->setError(neuronErr);
					
					// Now, for each input connection to this neuron, update its weight by:
					// Δw(t) = η * δ * in + μ * Δw(t-1)
					// η is learningRate
					// in is input from this connection (output of the previous neuron)
        			for (Connection *inConn : neuron->getInputConnections()) {

        				double weight = inConn->getWeight();
	        			double delta = properties->learningFunction->getLearningRate(epoch) * neuronErr * inConn->fromNeuron->getOutput() + properties->momentum * inConn->getDelta();
	        			inConn->setDelta(delta);
	        			if (properties->batchLearning) {
	        				inConn->setSummedDelta(inConn->getSummedDelta() + delta);
	        			} else {
	        				inConn->setWeight(weight + delta);
	        			}

        			}


        		}
				

    		}
			
			if (fabs(patternError) > properties->eps) errorCount++;

    	}

    	if (properties->batchLearning) {

        	for (NeuronLayer *layer : layers) {

        		for (Neuron *neuron : layer->getNeurons()) {

	    			for (Connection *inConn : neuron->getInputConnections()) {

	    				double weight = inConn->getWeight();
	        			inConn->setWeight(weight + inConn->getSummedDelta());
	        			inConn->setSummedDelta(0.0);

	    			}

        		}

        	}

    	}


    	epoch++;
    	errorRate = (double)errorCount / (double)trainingData->data.size();
		totalError = properties->costFunction->getMeanCost(totalError, (int)trainingData->data.size());
		
		if (totalError < bestError) {
			
			bestError = totalError;
			bestEpoch = epoch;
			
			bestWeights.clear();
			
			for (NeuronLayer *layer : layers) {
				
				for (Neuron *neuron : layer->getNeurons()) {
					
					for (Connection *conn : neuron->getOutputConnections()) {
						
						bestWeights.push_back(conn->getWeight());
						
					}
					
				}
				
			}
			
		}

    	if (properties->verbose)
			cout << "Epoch " << epoch << ", " << properties->costFunction->name << ": " << totalError << ", Error Rate: " << errorRate <<  ", LR: " << properties->learningFunction->getLearningRate(epoch) << endl;


    }

	if (signal_abort) {

		cout << "Training aborted." << endl;
		this->signal_abort = false;

	} else {

		cout << endl;
		cout << "Training complete" << endl;
		cout << "Epochs elapsed: " << epoch << endl;
		cout << properties->costFunction->name << ": " << totalError << endl;
		cout << "Error rate: " << errorRate << endl;
		cout << "Time elapsed: " << (time(0) - startTime) << " seconds" << endl;
		cout << "Best epoch: " << bestEpoch << ", with MSE: " << bestError << endl;
		cout << endl;

		if (properties->useBestEpoch) {

			int k = 0;
			for (NeuronLayer *layer : layers) {

				for (Neuron *neuron : layer->getNeurons()) {

					for (Connection *conn : neuron->getOutputConnections()) {

						conn->setWeight(bestWeights.at(k));
						k++;

					}

				}

			}

		}

		trained = true;

	}

}

void NeuralNetwork::test() {
	
	bool error = false;
	double errorRate;
	int errorCount = 0;
	int totalTests = 0;
	std::vector<double> outputs;
	
	//Start testing
	this->testing = true;
	for (DataRow *row : this->testingData->data) {

		if (this->signal_abort) break;
		
		outputs = this->run(row->inputs, this->properties->verbose);
		
		error = false;
		int expClassIndex = 0;
		for (int i = 0; i < row->outputs.size(); i++) {
			if (row->outputs[i] > row->outputs[expClassIndex]) expClassIndex = i;
		}
		
		int outClassIndex = 0;
		for (int i = 0; i < outputs.size(); i++) {
			if (outputs[i] > outputs[outClassIndex]) outClassIndex = i;
		}
		
		if (this->properties->verbose) {
		
			cout << "Expected: ";
			for (double e : row->outputs) {
				cout << e << ", ";
			}
			cout << endl;
			cout << "Passed? ";
			if (outClassIndex != expClassIndex) {
				
				cout << "NO";
				errorCount++;
				
			} else {
				
				cout << "YES";
				
			}
			cout << endl << endl;
			
		}
		
		totalTests++;
		
	}

	if (signal_abort) {

		cout << "Testing aborted." << endl;
		this->signal_abort = false;

	} else {

		errorRate = (double)errorCount / (double)totalTests;

		cout << "Testing finished." << endl;
		cout << "Accuracy: " << (1 - errorRate) << endl;

		this->accuracy = (1 - errorRate);

	}
	this->testing = false;
}

void NeuralNetwork::setVerbose(bool v) {
	this->properties->verbose = v;
}

NeuralNetworkProperties *NeuralNetwork::getProperties() {
	return this->properties;
}

Json::Value NeuralNetwork::generateJson() {
	
	Json::Value jNet;
	jNet["n_inputs"] = this->getNumberInputs();
	jNet["n_outputs"] = this->getNumberOutputs();
	jNet["properties"] = this->getProperties()->generateJson();
	jNet["trained"]	= this->trained;
	
	Json::Value jWeights;
	
	for (int k = 0; k < this->layers.size(); k++) {
		NeuronLayer *layer = this->layers.at(k);
		Json::Value jLayer;
		for (Neuron *neuron : layer->getNeurons()) {
			for (Connection *conn : neuron->getOutputConnections()) {
				
				jLayer.append(conn->getWeight());
				
			}
		}
		if (jLayer.size() > 0)
			jWeights.append(jLayer);
	}
	
	jNet["weights"] = jWeights;
	
	if (this->dataSet != NULL)
		jNet["dataSet"] = this->dataSet->generateJson();
	
	return jNet;
	
}

void NeuralNetwork::reset() {
	
	layers.clear();
	trained = false;
	testing = false;
	createLayers();
	if (this->dataSet != NULL) {
		std::random_shuffle(dataSet->data.begin(), dataSet->data.end());
		divideDataSet();
	}
	
}

void NeuralNetwork::abort() {
	this->signal_abort = true;
}

NeuralNetwork::~NeuralNetwork() {
	// TODO Auto-generated destructor stub
}

