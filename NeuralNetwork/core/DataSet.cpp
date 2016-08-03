//
//  DataSet.cpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/14/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include "DataSet.h"
#include <math.h>

DataRow::DataRow() {
	
	
}

DataRow::~DataRow() {
	
	
}

DataSet::DataSet(int n_inputs, int n_outputs) {
	
	this->n_inputs = n_inputs;
	this->n_outputs = n_outputs;
	
}

DataSet::DataSet(Json::Value json) {
	
	this->n_inputs = json["n_inputs"].asInt();
	this->n_outputs = json["n_outputs"].asInt();
	
	for (Json::Value jRow : json["rows"]) {
		
		std::vector<double> inputs;
		for (Json::Value input : jRow["inputs"]) {
			inputs.push_back(input.asDouble());
		}
		
		std::vector<double> outputs;
		for (Json::Value output : jRow["outputs"]) {
			outputs.push_back(output.asDouble());
		}
		
		DataRow *row = new DataRow();
		row->inputs = inputs;
		row->outputs = outputs;
		
		this->data.push_back(row);
		
	}
	
}

DataSet::~DataSet() {
	
	
}

void DataSet::normalize() {
	
	for (int i = 0; i < n_inputs; i++) {
		double mean = 0.0;
		double std = 0.0f;
		for (int j = 0; j < data.size(); j++) {
			mean += data.at(j)->inputs[i];
		}
		mean /= data.size();
		for (int j = 0; j < data.size(); j++) {
			std += (data.at(j)->inputs[i] - mean) * (data.at(j)->inputs[i] - mean);
		}
		
		std = sqrt(std / data.size());
		
		for (int j = 0; j < data.size(); j++) {
			data.at(j)->inputs[i] = (data.at(j)->inputs[i] - mean) / std;
		}
	}
	
}

Json::Value DataSet::generateJson() {
	
	Json::Value json;
	json["n_inputs"] = n_inputs;
	json["n_outputs"] = n_outputs;
	
	Json::Value jRowsArray;
	
	for (DataRow *row : this->data) {
		
		Json::Value jRow;
		
		for (double in : row->inputs) {
			jRow["inputs"].append(in);
		}
		for (double ou : row->outputs) {
			jRow["outputs"].append(ou);
		}
		
		jRowsArray.append(jRow);
		
	}
	
	json["rows"] = jRowsArray;
	
	return json;
	
}