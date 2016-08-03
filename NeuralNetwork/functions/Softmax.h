//
//  Softmax.h
//  NeuralNetwork
//
//  Created by Mayer Levy on 6/16/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef Softmax_h
#define Softmax_h

#include "TransferFunction.h"
#include "NeuronLayer.h"
#include <vector>

class Softmax : public TransferFunction {
public:

	Softmax();
	virtual ~Softmax();
	
	NeuronLayer * outputLayer;
	
	double getOutput(double x);
	double getDerivative(double x);
	
	void setOutputLayer(NeuronLayer* outputLayer);
	
};

#endif /* Softmax_h */
