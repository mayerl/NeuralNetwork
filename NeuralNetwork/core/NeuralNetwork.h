/*
 * NeuralNetwork.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "NeuralNetworkProperties.h"
#include "DataSet.h"
#include "NeuronLayer.h"
#include "json/json.h"
#include <vector>

class NeuralNetwork {
public:

	virtual ~NeuralNetwork();

	std::vector<NeuronLayer*> layers;
	bool trained = false;
	bool testing = false;
	double accuracy;

	NeuralNetwork(int n_inputs, int n_outputs);
	NeuralNetwork(int n_inputs, int n_outputs, NeuralNetworkProperties *properties);
	NeuralNetwork(Json::Value json);
	void setDataSet(DataSet *data);
	DataSet *getDataSet();
	DataSet *getTrainingData();
	DataSet *getTestingData();
	int getNumberInputs();
	int getNumberOutputs();
	std::vector<double> run(std::vector<double> in, bool verbose);
	void train() throw ();
	void test();
	void setVerbose(bool v);
	NeuralNetworkProperties *getProperties();
	Json::Value generateJson();
	void reset();
	void setTrainingData(DataSet *data);
	void setTestingData(DataSet *data);

private:

	NeuralNetworkProperties *properties;
	int n_inputs;
	int n_outputs;
	DataSet *dataSet;
	DataSet *trainingData;
	DataSet *testingData;
	
	void createLayers();
	void divideDataSet();


};

#endif /* NEURALNETWORK_H_ */
