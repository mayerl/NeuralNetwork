/*
 * ConstantLearningRateFunction.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef CONSTANTLEARNINGRATEFUNCTION_H_
#define CONSTANTLEARNINGRATEFUNCTION_H_

#include "LearningRateFunction.h"

class ConstantLearningRateFunction : public LearningRateFunction {
public:
	ConstantLearningRateFunction();
	virtual ~ConstantLearningRateFunction();

	ConstantLearningRateFunction(double learningRate);
	ConstantLearningRateFunction(Json::Value json);
	double getLearningRate(int epoch);
	Json::Value generateJson();
};

#endif /* CONSTANTLEARNINGRATEFUNCTION_H_ */
