/*
 * WeightedSum.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef WEIGHTEDSUM_H_
#define WEIGHTEDSUM_H_

#include "InputFunction.h"
#include "Connection.h"
#include <vector>

class WeightedSum : public InputFunction {
public:
	WeightedSum();
	virtual ~WeightedSum();

    double getOutput(std::vector<Connection*> inputConnections);

};

#endif /* WEIGHTEDSUM_H_ */
