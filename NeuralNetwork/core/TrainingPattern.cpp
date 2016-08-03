/*
 * TrainingPattern.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "TrainingPattern.h"

TrainingPattern::TrainingPattern(int n_inputs, int n_outputs) {
    this->inputs.reserve(n_inputs);
    this->outputs.reserve(n_outputs);
}

TrainingPattern::TrainingPattern(std::vector<double> inputs, std::vector<double> outputs) {
	this->inputs = inputs;
	this->outputs = outputs;
}

TrainingPattern::~TrainingPattern() {
	// TODO Auto-generated destructor stub
}

