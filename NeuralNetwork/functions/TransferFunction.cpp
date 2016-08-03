/*
 * TransferFunction.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: mayerlevy
 */

#include "TransferFunction.h"

TransferFunction::TransferFunction() {
	// TODO Auto-generated constructor stub

}

TransferFunction::~TransferFunction() {
	// TODO Auto-generated destructor stub
}

double TransferFunction::getOutput(double x) {
    return 0.0f;
}
double TransferFunction::getDerivative(double x) {
    return 0.0f;
}

Json::Value TransferFunction::generateJson() {
	Json::Value json;
	json["type"] = this->type;
	
	return json;
}