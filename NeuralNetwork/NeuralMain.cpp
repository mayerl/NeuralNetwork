//
//  NeuralMain.cpp
//  NeuralNetwork
//
//  Created by Mayer Levy on 7/27/16.
//  Copyright © 2016 Mayer Levy. All rights reserved.
//

#include <pthread.h>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "NeuralHeader.h"

using namespace std;

bool abortOp = false;

int Get_Key (void) {
	int key;
	struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt); // 1473
	memcpy((void *)&newt, (void *)&oldt, sizeof(struct termios));
	newt.c_lflag &= ~(ICANON);  // Reset ICANON
	newt.c_lflag &= ~(ECHO);    // Echo off, after these two .c_lflag = 1217
	tcsetattr( STDIN_FILENO, TCSANOW, &newt); // 1217
	key=getchar(); // works like "getch()"
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return key;
}

struct threadTraining_args {
	NeuralNetwork* net;
};

void *threadTraining(void *argp) {
	
	struct threadTraining_args *args = (struct threadTraining_args*)argp;
	args->net->train();
	
	return NULL;
	
}

void *threadTesting(void *argp) {
	
	struct threadTraining_args *args = (struct threadTraining_args*)argp;
	args->net->test();
	
	return NULL;
	
}

void *threadCommand(void *argp) {
	
	struct threadTraining_args *args = (struct threadTraining_args*)argp;
	
	do {
		
		char c = Get_Key();
		
		if (c == 'q') {
			
			abortOp = true;
			
		} else if (c == 'v') {
			
			args->net->setVerbose(!args->net->getProperties()->verbose);
			
		}
		
	} while (!abortOp);
	
	return NULL;
}

void runNeuralNetwork() {
	
	// Update the random seed according to current time
	srand((unsigned)time(NULL));
	
	NeuralNetwork *net = NULL;
	
	cout << "Welcome to Neural Network" << endl;
	string cmd;
	
	do {
	
		if (!cmd.compare("init")) {
			
			initNeuralNetwork(&net);
			
		} else if (!cmd.compare("data")) {
			
			loadDataset(net);
			
		} else if (!cmd.compare("train")) {
			
			if (net == NULL) {
				
				cout << "Network not initialized!" << endl;
				
			} else if (net->getTrainingData() == NULL) {
				
				cout << "No dataset found!" << endl;
				
			} else if (net->trained) {
				
				cout << "Network already trained. If you wish to train again reset the network first." << endl;
				
			} else {
				
				abortOp = false;
				
				char verbose;
				cout << "Verbose mode on? [y/n]: ";
				cin >> verbose;
				if (verbose == 'y')
					net->setVerbose(true);
				else
					net->setVerbose(false);
				
				cout << "Training in progress..." << endl;
				cout << "Type 'q' to quit or 'v' to see progress" << endl;
				
				// Start training
				pthread_t trainingThread;
				pthread_t commandThread;
				struct threadTraining_args t_params;
				t_params.net = net;
				pthread_create(&trainingThread, NULL, threadTraining, &t_params);
				pthread_create(&commandThread, NULL, threadCommand, &t_params);
				
				while (!net->trained && !abortOp);
				
				abortOp = true;
				
				pthread_cancel(trainingThread);
				pthread_cancel(commandThread);
				
				if (!net->trained) {
					cout << "Training aborted by user!" << endl;
				}
				
			}
			
		} else if (!cmd.compare("test")) {
			
			if (net == NULL) {
				
				cout << "Network not initialized!" << endl;
				
			} else if (net->getTestingData() == NULL) {
					
				cout << "No dataset found!" << endl;
				
			} else {
			
				abortOp = false;
				
				char verbose;
				cout << "Verbose mode on? [y/n]: ";
				cin >> verbose;
				if ( verbose == 'y')
					net->setVerbose(true);
				else
					net->setVerbose(false);
				
				cout << "Testing in progress..." << endl;
				cout << "Type 'q' to quit or 'v' to toggle verbose" << endl << endl;
				
				// Start training
				pthread_t testingThread;
				pthread_t commandThread;
				struct threadTraining_args t_params;
				t_params.net = net;
				pthread_create(&testingThread, NULL, threadTesting, &t_params);
				pthread_create(&commandThread, NULL, threadCommand, &t_params);
				
				net->testing = true;
				
				while (net->testing && !abortOp);
				
				abortOp = true;
				
				pthread_cancel(testingThread);
				pthread_cancel(commandThread);
				
				if (net->testing) {
					cout << "Testing aborted by user!" << endl;
				}
				
			}
			
		} else if (!cmd.compare("save")) {
			
			saveNeuralNetwork(net);
			
		} else if (!cmd.compare("load")) {
			
			loadNeuralNetwork(&net);
			
		} else if (!cmd.compare("view")) {
			
			viewNeuralNetwork(net);
			
		} else if (!cmd.compare("batch")) {
			
			batchRunNeuralNetwork(net);
		
		} else if (!cmd.compare("reset")) {
			
			if (net == NULL) {
				
				cout << "Network not initialized!" << endl;
				
			} else {
			
				net->reset();
				cout << "Network reset!" << endl;
				
			}
		
		} else if (!cmd.compare("quit")) {
			
			break;
			
		}
		
		cout << endl;
		cout << "Select your option: " << endl;
		cout << "\tinit: Initialize network" << endl;
		cout << "\tdata:  Set network's dataset" << endl;
		cout << "\ttrain: Train network" << endl;
		cout << "\ttest: Test network" << endl;
		cout << "\tsave: Save network" << endl;
		cout << "\tload: Load network" << endl;
		cout << "\tview: View network" << endl;
		cout << "\tbatch: Batch run network" << endl;
		cout << "\tquit: Quit" << endl;
		cout << ": ";
		
	} while (cin >> cmd);
	
	return;
	
}

void initNeuralNetwork(NeuralNetwork **net) {
	
	cout << endl;
	
	int n_inputs = 12;
	int n_outputs = 2;
	double eps = 0.1;
	double minErrorRate = 0.001;
	double momentum = 0.1;
	double maxIte = 1000;
	int n_hiddenLayers = 1;
	int n_hiddenNeurons = 10;
	double trainingProportion = 0.8;
	int i;
	char c;
	bool batchLearning = false;
	bool bestEpoch = false;
	TransferFunction *h_transferFunc = NULL;
	TransferFunction *o_transferFunc = NULL;
	LearningRateFunction *learningFunc = NULL;
	CostFunction *costFunc = NULL;
	
	// Request user for configurations parameters
	cout << "Number of inputs: ";
	cin >> n_inputs;
	cout << "Number of outputs: ";
	cin >> n_outputs;
	cout << "Number of hidden layers: ";
	cin >> n_hiddenLayers;
	cout << "Number of neurons per hidden layer: ";
	cin >> n_hiddenNeurons;
	while (h_transferFunc == NULL) {
		cout << "Activation function for hidden layers: " << endl;
		cout << "\t0: Step\n\t1: Sigmoid\n\t2: Tanh\n\t3: Softmax" << endl;
		cin >> i;
		switch (i) {
			case STEP:
				h_transferFunc = new Step();
				break;
			case SIGMOID:
				h_transferFunc = new Sigmoid();
				break;
			case TANH:
				h_transferFunc = new Tanh();
				break;
			case SOFTMAX:
				h_transferFunc = new Softmax();
				break;
			default:
				cout << "Invalid transfer function!" << endl;
				
		}
	}
	while (o_transferFunc == NULL) {
		cout << "Activation function for output layer: " << endl;
		cout << "\t0: Step\n\t1: Sigmoid\n\t2: Tanh\n\t3: Softmax" << endl;
		cin >> i;
		switch (i) {
			case STEP:
				o_transferFunc = new Step();
				break;
			case SIGMOID:
				o_transferFunc = new Sigmoid();
				break;
			case TANH:
				o_transferFunc = new Tanh();
				break;
			case SOFTMAX:
				o_transferFunc = new Softmax();
				break;
			default:
				cout << "Invalid transfer function!" << endl;
				
		}
	}
	cout << "Tolerance (default 0.1): ";
	cin >> eps;
	cout << "Momentum (default 0.5): ";
	cin >> momentum;
	cout << "Max Iterations: ";
	cin >> maxIte;
	cout << "Min error rate (default 0.01): ";
	cin >> minErrorRate;
	while (learningFunc == NULL) {
		cout << "Learning Function: " << endl;
		cout << "\t0: Constant\n\t1: Linear\n\t2: Exponential" << endl;
		cin >> i;
		switch (i) {
			case CONSTANT: {
				double l_rate;
				cout << "Learning Rate: ";
				cin >> l_rate;
				learningFunc = new ConstantLearningRateFunction(l_rate);
				break;
			}
			case LINEAR: {
				double l_rate, fl_rate, slope;
				cout << "Initial Learning Rate: ";
				cin >> l_rate;
				cout << "Final Learning Rate: ";
				cin >> fl_rate;
				cout << "Slope: ";
				cin >> slope;
				learningFunc = new LinearLearningRateFunction(l_rate, fl_rate, slope);
				break;
			}
			case EXPONENTIAL: {
				double l_rate, t_const;
				cout << "Learning Rate: ";
				cin >> l_rate;
				cout << "Time constant ";
				cin >> t_const;
				cout << "Slope: ";
				learningFunc = new ExponentialLearningRateFunction(l_rate, t_const);
				break;
			}
			default:
				cout << "Invalid learning function!" << endl;
				
		}
	}
	while (costFunc == NULL) {
		cout << "Cost function (error function): " << endl;
		cout << "\t0: Quadratic\n\t1: Cross-Entropy" << endl;
		cin >> i;
		switch (i) {
			case QUADRATIC:
				costFunc = new QuadraticCostFunction();
				break;
			case CROSS_ENTROPY:
				costFunc = new CrossEntropyCostFunction();
				break;
			default:
				cout << "Invalid cost function!" << endl;
				
		}
	}
	cout << "Use batch learning? (y/n): ";
	cin >> c;
	if (c == 'y') batchLearning = true;
	else batchLearning = false;
	cout << "Use the best epoch weights as the final weights? (y/n): ";
	cin >> c;
	if (c == 'y') bestEpoch = true;
	else bestEpoch = false;
	cout << "Training set proportion (default: 0.8): ";
	cin >> trainingProportion;
	
	NeuralNetworkProperties *properties = new NeuralNetworkProperties();
	
	properties->momentum = momentum;
	properties->eps = eps;
	properties->batchLearning = batchLearning;
	properties->maxIte = maxIte;
	properties->minErrorRate = minErrorRate;
	properties->n_hiddenLayers = n_hiddenLayers;
	properties->n_hiddenNeurons = n_hiddenNeurons;
	properties->learningFunction = learningFunc;
	properties->hiddenTransferFunction = h_transferFunc;
	properties->outputTransferFunction = o_transferFunc;
	properties->costFunction = costFunc;
	properties->useBestEpoch = bestEpoch;
	properties->trainingProportion = trainingProportion;
	
	*net = new NeuralNetwork(n_inputs,n_outputs,properties);
	
	cout << "Network initialized!" << endl;
	
}

void loadDataset(NeuralNetwork *net) {
	
	if (net == NULL) {
		
		cout << "Network not initialized or loaded!" << endl;
		
	} else {
		
		string fileName;
		
		ifstream in;
		bool opened = false;
		
		do {
			
			cout << "Please, type the dataset file name: ";
			cin >> fileName;
			
			in.open(fileName);
			
			if (in.is_open()) {
				opened = true;
			} else {
				cout << "File could not be opened!" << endl;
			}
			
		} while (!opened);
		
		DataSet *dataSet = NULL;
		
		int n_inputs = net->getNumberInputs();
		int n_outputs = net->getNumberOutputs();
		dataSet = new DataSet(n_inputs, n_outputs);
		
		int count = 0;
		
		std::string line;
		
		string sCurrentLine;
		std::vector<double> inputs;
		
		// Read the dataset file and populate the dataSet object with it.
		while (getline(in, line)) {
			vector<string> values = Util::split(line,',');
			DataRow *row = new DataRow();
			for (int i = 0; i < n_inputs; i++) {
				row->inputs.push_back(stod(values[i]));
			}
			for (int i = n_inputs; i < n_inputs+n_outputs; i++) {
				row->outputs.push_back(stod(values[i]));
			}
			dataSet->data.push_back(row);
			count++;
		}
		
		in.close();
		
		dataSet->normalize();
		
		std::random_shuffle(dataSet->data.begin(), dataSet->data.end());
		
		net->setDataSet(dataSet);
		
		cout << "Dataset loaded!" << endl;
		
	}
	
}

void trainNeuralNetwork(NeuralNetwork *net) {
	
	net->train();
	
}

void testNeuralNetwork(NeuralNetwork *net) {
	
	net->test();
	
}

void saveNeuralNetwork(NeuralNetwork *net) {
	
	string fileName;
	ofstream ou;
	bool opened = false;
	
	do {
		
		cout << "Please type the name of the output file: ";
		cin >> fileName;
		
		ou.open(fileName);
		
		if (ou.is_open()) {
			opened = true;
		} else {
			cout << "File could not be opened!" << endl;
		}
		
	} while (!opened);
	
	Json::Value jNet = net->generateJson();
	
	ou << jNet.toStyledString();
	
	ou.close();
	
	cout << "File saved successfully!" << endl;
	
	
}

void loadNeuralNetwork(NeuralNetwork **net) {
	
	string fileName;
	ifstream in;
	bool opened = false;
	
	do {
		
		cout << "Please type the name of the input Json file: ";
		cin >> fileName;
		
		in.open(fileName);
		
		if (in.is_open()) {
			opened = true;
		} else {
			cout << "File could not be opened!" << endl;
		}
		
	} while (!opened);
	
	Json::Value json;
	
	in >> json;

	*net = new NeuralNetwork(json);

	in.close();
	
	cout << "File loaded successfully!" << endl;

	
}

void viewNeuralNetwork(NeuralNetwork *net) {
	
	if (net == NULL) {
		
		cout << "Network not initialized!" << endl;
		
	} else {
	
		Json::Value jNet = net->generateJson();
		cout << jNet;
		
	}
	
}

void batchRunNeuralNetwork(NeuralNetwork *net) {
	
	if (net == NULL) {
		
		cout << "Network not initialized!" << endl;
		
	} else if (net->getDataSet() == NULL) {
		
		cout << "No dataset found!" << endl;
		
	} else {
		
		int n;
		cout << "How many times should the network run? ";
		cin >> n;
		
		std::vector<double> results;
		
		for (int i = 0; i < n; i++) {
			
			net->reset();
			net->train();
			net->test();
			
			results.push_back(net->accuracy);
			
		}
		
		cout << endl;
		cout << "Batch finished." << endl;
		cout << "Results: ";
		for (double d : results) cout << d << ",";
		cout << endl;
		cout << endl;
		
		std::sort(results.begin(), results.end());
		
		int size = (int)results.size();
		int mid = (int)floor(size/2);
		double min, Q1, med, Q3, max;
		
		min = results.at(0);
		max = results.at(size - 1);
		med = Util::median(results.begin(), results.end());
		Q1 = Util::median(results.begin(), results.end() - mid);
		Q3 = Util::median(results.begin() + mid, results.end());

		cout << "min: " << min << endl;
		cout << "Q1: " << Q1 << endl;
		cout << "med: " << med << endl;
		cout << "Q3: " << Q3 << endl;
		cout << "max: " << max << endl;
		
	}
	
}