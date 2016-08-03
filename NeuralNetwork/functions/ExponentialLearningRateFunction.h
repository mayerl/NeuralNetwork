/*
 * ExponentialLearningRateFunction.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef EXPONENTIALLEARNINGRATEFUNCTION_H_
#define EXPONENTIALLEARNINGRATEFUNCTION_H_

#include "LearningRateFunction.h"

class ExponentialLearningRateFunction : public LearningRateFunction {
public:
	virtual ~ExponentialLearningRateFunction();

	ExponentialLearningRateFunction(double learningRate, double timeConstant);
	ExponentialLearningRateFunction(Json::Value json);
	double getLearningRate(int epoch);
	Json::Value generateJson();


private:
	double timeConstant;

};

#endif /* EXPONENTIALLEARNINGRATEFUNCTION_H_ */
