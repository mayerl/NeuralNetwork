//
//  CrossEntropyCostFunction.h
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/10/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef CrossEntropyCostFunction_h
#define CrossEntropyCostFunction_h

#include <stdio.h>

#include "CostFunction.h"

class CrossEntropyCostFunction : public CostFunction {
public:
	CrossEntropyCostFunction();
	virtual ~CrossEntropyCostFunction();
	
	double getCost(double output, double target);
	double getGradient(double output, double target);
	double getMeanCost(double summedCost, int samples);
	
	
};

#endif /* CrossEntropyCostFunction_h */
