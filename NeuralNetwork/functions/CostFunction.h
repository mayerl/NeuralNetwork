//
//  ErrorFunction.hpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/10/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef CostFunction_h
#define CostFunction_h

#include <stdio.h>
#include <string>
#include "../json/json.h"

typedef enum {QUADRATIC, CROSS_ENTROPY} costFuncTypes;

class CostFunction {
public:
	CostFunction();
	virtual ~CostFunction();
	
	std::string name;
	
	virtual double getCost(double output, double target) = 0;
	virtual double getGradient(double output, double target) = 0;
	virtual double getMeanCost(double summedCost, int samples) = 0;
	Json::Value generateJson();
	
protected:
	costFuncTypes type;
	
};

#endif /* CostFunction_h */
