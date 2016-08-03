/*
 * LearningRateFunction.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef LEARNINGRATEFUNCTION_H_
#define LEARNINGRATEFUNCTION_H_

#include <string>
#include "json/json.h"

typedef enum {CONSTANT, LINEAR, EXPONENTIAL} learningFuncTypes;

class LearningRateFunction {
public:
    LearningRateFunction();
	virtual ~LearningRateFunction();

	double learningRate;
	
	virtual double getLearningRate(int epoch);
	LearningRateFunction(double learningRate);
	LearningRateFunction(Json::Value json);
	virtual Json::Value generateJson() = 0;
	
protected:
	learningFuncTypes type;
};

#endif /* LEARNINGRATEFUNCTION_H_ */
