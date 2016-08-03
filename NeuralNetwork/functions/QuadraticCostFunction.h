//
//  QuadraticCostFunction.h
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/10/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef QuadraticCostFunction_h
#define QuadraticCostFunction_h

#include <stdio.h>
#include "CostFunction.h"

class QuadraticCostFunction : public CostFunction {
	
public:
	QuadraticCostFunction();
	virtual ~QuadraticCostFunction();
	
	double getCost(double output, double target);
	double getGradient(double output, double target);
	double getMeanCost(double summedCost, int samples);
	
	
};

#endif /* QuadraticCostFunction_h */
