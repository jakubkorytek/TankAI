#pragma once
#include <stdlib.h>
#include <vector>

using namespace std;

class Neuron
{
public:
	Neuron() {};
	~Neuron() {};

	double initNeuron() { return ((double)rand()) / RAND_MAX; }

	vector<double> listOfWeightIn;
	vector<double> listOfWeightOut;
	double outputValue;
	double error;
	double sensibility;

private:

};
