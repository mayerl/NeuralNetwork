//
//  DataSet.h
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/14/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef DataSet_h
#define DataSet_h

#include <stdio.h>
#include <vector>
#include "../json/json.h"

class DataRow {
public:
	
	std::vector<double> inputs;
	std::vector<double> outputs;
	
	DataRow();
	virtual ~DataRow();
	
};

class DataSet {
public:
	
	std::vector<DataRow *> data;
	int n_inputs;
	int n_outputs;
	
	void normalize();
	
	DataSet(int n_inputs, int n_outputs);
	DataSet(Json::Value json);
	virtual ~DataSet();
	Json::Value generateJson();
	
};

#endif /* DataSet_h */
