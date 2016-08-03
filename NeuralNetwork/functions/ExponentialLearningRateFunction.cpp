/*
 * ExponentialLearningRateFunction.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "ExponentialLearningRateFunction.h"
#include <cmath>

ExponentialLearningRateFunction::~ExponentialLearningRateFunction() {
	// TODO Auto-generated destructor stub
}

ExponentialLearningRateFunction::ExponentialLearningRateFunction(double learningRate, double timeConstant) : LearningRateFunction(learningRate) {

	this->type = EXPONENTIAL;
    this->timeConstant = timeConstant;
	
}

ExponentialLearningRateFunction::ExponentialLearningRateFunction(Json::Value json) : LearningRateFunction(json) {
	
	this->type = EXPONENTIAL;
	this->timeConstant = json["timeConstant"].asDouble();
	
}

double ExponentialLearningRateFunction::getLearningRate(int epoch) {
	return learningRate * exp(-timeConstant * epoch);
}

Json::Value ExponentialLearningRateFunction::generateJson() {
	
	Json::Value json;
	json["type"] = this->type;
	json["learningRate"] = this->learningRate;
	json["timeConstant"] = this->timeConstant;
	
	return json;
	
}

