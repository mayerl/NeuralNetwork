/*
 * TrainingPattern.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef TRAININGPATTERN_H_
#define TRAININGPATTERN_H_

#include <vector>

class TrainingPattern {
public:
	TrainingPattern();
	virtual ~TrainingPattern();

    std::vector<double> inputs;
    std::vector<double> outputs;

	TrainingPattern(int n_inputs, int n_outputs);
	TrainingPattern(std::vector<double> inputs, std::vector<double> outputs);

};

#endif /* TRAININGPATTERN_H_ */
