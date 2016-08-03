/*
 * NeuralNetworkProperties.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef NEURALNETWORKPROPERTIES_H_
#define NEURALNETWORKPROPERTIES_H_

#include "TransferFunction.h"
#include "LearningRateFunction.h"
#include "CostFunction.h"
#include "json/json.h"

class NeuralNetworkProperties {
public:
	NeuralNetworkProperties();
	NeuralNetworkProperties(Json::Value json);
	virtual ~NeuralNetworkProperties();
	Json::Value generateJson();

	LearningRateFunction *learningFunction;
	double momentum;
	double eps;
	double minErrorRate;
	int maxIte;
	bool batchLearning;
	int n_hiddenLayers;
	int n_hiddenNeurons;
	bool useBestEpoch;
	bool verbose;
	double trainingProportion;
	CostFunction *costFunction;
	TransferFunction *hiddenTransferFunction;
	TransferFunction *outputTransferFunction;


};

#endif /* NEURALNETWORKPROPERTIES_H_ */
