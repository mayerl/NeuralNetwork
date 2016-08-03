/*
 * LinearLearningRateFunction.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "LinearLearningRateFunction.h"

LinearLearningRateFunction::LinearLearningRateFunction(double learningRate, double finalLearningRate, double slope) : LearningRateFunction(learningRate) {
	
	this->type = LINEAR;
	this->finalLearningRate = finalLearningRate;
	this->slope = slope;

}

LinearLearningRateFunction::LinearLearningRateFunction(Json::Value json) : LearningRateFunction(json) {
	
	this->type = LINEAR;
	this->finalLearningRate = json["finalLearningRate"].asDouble();
	this->slope = json["slope"].asDouble();
	
}

LinearLearningRateFunction::~LinearLearningRateFunction() {
	// TODO Auto-generated destructor stub
}

double LinearLearningRateFunction::getLearningRate(int epoch) {
	return -(learningRate - finalLearningRate)/slope * epoch + learningRate;
}

Json::Value LinearLearningRateFunction::generateJson() {
	
	Json::Value json;
	json["type"] = this->type;
	json["learningRate"] = this->learningRate;
	json["finalLearningRate"] = this->finalLearningRate;
	json["slope"] = this->slope;
	
	return json;
	
}

