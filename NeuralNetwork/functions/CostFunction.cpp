//
//  ErrorFunction.cpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/10/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include "CostFunction.h"

CostFunction::CostFunction() {
	
}

CostFunction::~CostFunction() {
	
}

Json::Value CostFunction::generateJson() {
	Json::Value json;
	json["type"] = this->type;
	
	return json;
}