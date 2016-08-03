/*
 * LearningRateFunction.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "LearningRateFunction.h"

LearningRateFunction::LearningRateFunction(double learningRate) {
	this->learningRate = learningRate;
}

LearningRateFunction::LearningRateFunction(Json::Value json) {
	this->learningRate = json["learningRate"].asDouble();
}

LearningRateFunction::LearningRateFunction() {
    // TODO Auto-generated destructor stub
}

LearningRateFunction::~LearningRateFunction() {
	// TODO Auto-generated destructor stub
}

double LearningRateFunction::getLearningRate(int epoch) {
    return 0.0f;
}
