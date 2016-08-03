/*
 * InputFunction.h
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#ifndef INPUTFUNCTION_H_
#define INPUTFUNCTION_H_

#include "Connection.h"
#include <vector>

class InputFunction {
public:
	InputFunction();
	virtual ~InputFunction();

    virtual double getOutput(std::vector<Connection*> inputConnections);

};

#endif /* INPUTFUNCTION_H_ */
