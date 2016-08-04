//
//  NeuralHeader.h
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/27/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#ifndef NeuralHeader_h
#define NeuralHeader_h

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <algorithm>

#include "util/Util.hpp"

#include "json/json.h"

#include "functions/TransferFunction.h"
#include "functions/Step.h"
#include "functions/Sigmoid.h"
#include "functions/Tanh.h"
#include "functions/LearningRateFunction.h"
#include "functions/ConstantLearningRateFunction.h"
#include "functions/ExponentialLearningRateFunction.h"
#include "functions/LinearLearningRateFunction.h"
#include "core/NeuralNetworkProperties.h"
#include "core/Connection.h"
#include "functions/InputFunction.h"
#include "functions/WeightedSum.h"
#include "functions/Softmax.h"
#include "neuron/Neuron.h"
#include "neuron/BiasNeuron.h"
#include "neuron/InputNeuron.h"
#include "core/NeuronLayer.h"
#include "core/TrainingPattern.h"
#include "core/NeuralNetwork.h"
#include "core/ConnectionFactory.h"
#include "functions/CrossEntropyCostFunction.h"
#include "functions/QuadraticCostFunction.h"
#include "core/DataSet.h"

void runNeuralNetwork();
void initNeuralNetwork(NeuralNetwork **net);
void loadDataset(NeuralNetwork *net);
void trainNeuralNetwork(NeuralNetwork *net);
void testNeuralNetwork(NeuralNetwork *net);
void saveNeuralNetwork(NeuralNetwork *net);
void loadNeuralNetwork(NeuralNetwork **net);
void viewNeuralNetwork(NeuralNetwork *net);
void batchRunNeuralNetwork(NeuralNetwork *net);


#endif /* NeuralHeader_h */
