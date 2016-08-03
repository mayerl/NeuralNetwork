/*
 * NeuralNetworkProperties.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "NeuralNetworkProperties.h"
#include "ConstantLearningRateFunction.h"
#include "LinearLearningRateFunction.h"
#include "ExponentialLearningRateFunction.h"
#include "Step.h"
#include "Sigmoid.h"
#include "Tanh.h"
#include "Softmax.h"
#include "QuadraticCostFunction.h"
#include "CrossEntropyCostFunction.h"
#include <typeinfo>

NeuralNetworkProperties::NeuralNetworkProperties() {
	this->learningFunction = new ConstantLearningRateFunction(0.01);
	this->momentum = 0.01;
	this->eps = 0.1;
	this->minErrorRate = 0.05;
	this->batchLearning = false;
	this->maxIte = 10000;
	this->n_hiddenLayers = 1;
	this->n_hiddenNeurons = 10;
	this->hiddenTransferFunction = new Sigmoid();
	this->outputTransferFunction = new Sigmoid();
	this->costFunction = new QuadraticCostFunction();
	this->useBestEpoch = false;
	this->verbose = false;
	this->trainingProportion = 0.8;
}

NeuralNetworkProperties::NeuralNetworkProperties(Json::Value json) {
	Json::Value jLearningFunction = json["learningFunction"];
	switch (jLearningFunction["type"].asInt()) {
		case CONSTANT:
			this->learningFunction = new ConstantLearningRateFunction(jLearningFunction);
		break;
		case LINEAR:
			this->learningFunction = new LinearLearningRateFunction(jLearningFunction);
		break;
		case EXPONENTIAL:
			this->learningFunction = new ExponentialLearningRateFunction(jLearningFunction);
		break;
	}
	this->momentum = json["momentum"].asDouble();
	this->eps = json["eps"].asDouble();
	this->minErrorRate = json["minErrorRate"].asDouble();
	this->batchLearning = json["batchLearning"].asBool();
	this->maxIte = json["maxIte"].asInt();
	this->n_hiddenLayers = json["n_hiddenLayers"].asInt();
	this->n_hiddenLayers = json["n_hiddenNeurons"].asInt();
	Json::Value jHiddenTransfFunc = json["hiddenTransferFunction"];
	switch (jHiddenTransfFunc["type"].asInt()) {
		case STEP:
			this->hiddenTransferFunction = new Step();
			break;
		case SIGMOID:
			this->hiddenTransferFunction = new Sigmoid();
			break;
		case TANH:
			this->hiddenTransferFunction = new Tanh();
			break;
		case SOFTMAX:
			this->hiddenTransferFunction = new Softmax();
			break;
	}
	Json::Value jOutputTransfFunc = json["outputTransferFunction"];
	switch (jOutputTransfFunc["type"].asInt()) {
		case STEP:
			this->outputTransferFunction = new Step();
			break;
		case SIGMOID:
			this->outputTransferFunction = new Sigmoid();
			break;
		case TANH:
			this->outputTransferFunction = new Tanh();
			break;
		case SOFTMAX:
			this->outputTransferFunction = new Softmax();
			break;
	}
	Json::Value jCostFunction = json["costFunction"];
	switch (jCostFunction["type"].asInt()) {
		case QUADRATIC:
			this->costFunction = new QuadraticCostFunction();
			break;
		case CROSS_ENTROPY:
			this->costFunction = new CrossEntropyCostFunction();
			break;
	}
	this->useBestEpoch = json["useBestEpoch"].asBool();
	this->verbose = json["verbose"].asBool();
	this->trainingProportion = json["trainingProportion"].asDouble();
}

Json::Value NeuralNetworkProperties::generateJson() {
	
	Json::Value jProperties;
	jProperties["learningFunction"]			= this->learningFunction->generateJson();
	jProperties["momentum"]					= this->momentum;
	jProperties["eps"]						= this->eps;
	jProperties["minErrorRate"]				= this->minErrorRate;
	jProperties["batchLearning"]			= this->batchLearning;
	jProperties["maxIte"]					= this->maxIte;
	jProperties["n_hiddenLayers"]			= this->n_hiddenLayers;
	jProperties["n_hiddenNeurons"]			= this->n_hiddenNeurons;
	jProperties["hiddenTransferFunction"]	= this->hiddenTransferFunction->generateJson();
	jProperties["outputTransferFunction"]	= this->outputTransferFunction->generateJson();
	jProperties["costFunction"]				= this->costFunction->generateJson();
	jProperties["useBestEpoch"]				= this->useBestEpoch;
	jProperties["verbose"]					= this->verbose;
	jProperties["trainingProportion"]		= this->trainingProportion;
	
	return jProperties;
	
}

NeuralNetworkProperties::~NeuralNetworkProperties() {
	// TODO Auto-generated destructor stub
}

