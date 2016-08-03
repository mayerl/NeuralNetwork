/*
 * ConstantLearningRateFunction.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "ConstantLearningRateFunction.h"

ConstantLearningRateFunction::ConstantLearningRateFunction(double learningRate) : LearningRateFunction(learningRate) {
	
	this->type = CONSTANT;

}

ConstantLearningRateFunction::ConstantLearningRateFunction(Json::Value json) : LearningRateFunction(json) {
	
	this->type = CONSTANT;
	
}

double ConstantLearningRateFunction::getLearningRate(int epoch) {
		return this->learningRate;
	}

ConstantLearningRateFunction::~ConstantLearningRateFunction() {
	// TODO Auto-generated destructor stub
}

Json::Value ConstantLearningRateFunction::generateJson() {
	
	Json::Value json;
	json["type"] = this->type;
	json["learningRate"] = this->learningRate;
	
	return json;
	
}