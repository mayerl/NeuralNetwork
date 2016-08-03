/*
 * LinearLearningRateFunction.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef LINEARLEARNINGRATEFUNCTION_H_
#define LINEARLEARNINGRATEFUNCTION_H_

#include "LearningRateFunction.h"

class LinearLearningRateFunction : public LearningRateFunction {
public:
	LinearLearningRateFunction();
	virtual ~LinearLearningRateFunction();

	LinearLearningRateFunction(double learningRate, double finalLearningRate, double slope);
	LinearLearningRateFunction(Json::Value json);
	double getLearningRate(int epoch);
	Json::Value generateJson();


private:
	double finalLearningRate;
	double slope;

};

#endif /* LINEARLEARNINGRATEFUNCTION_H_ */
