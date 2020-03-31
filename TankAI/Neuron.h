#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include "MathUtils.h"

using namespace std;

class Neuron
{
public:
	Neuron(int numberOfConnections, double bias);
	~Neuron();

	double bias;
	double error;
	double outputValue;
	
	vector<double> weightsIn;

	double calculateOutputValue(vector<double> inputs);
	void printNeuron();

private:

};

inline Neuron::Neuron(int numberOfConnections, double bias)
{
	for (int i = 0; i < numberOfConnections; ++i)
	{
		weightsIn.push_back(((double)rand() / (RAND_MAX))-0.5);
	}
	this->error = 0;
	this->bias = bias;
}

inline Neuron::~Neuron()
{
}

inline double Neuron::calculateOutputValue(vector<double> inputs)
{
	double tempOutputValue = this->bias;

	for (int i = 0;i < inputs.size();++i)
	{
		tempOutputValue += inputs[i] * weightsIn[i];
	}
	this->outputValue = MathUtils::sigmoid(tempOutputValue);
	return this->outputValue;
}

inline void Neuron::printNeuron()
{
	for (int i = 0; i < weightsIn.size();++i)
	{
		cout << "W" << i << " : " << weightsIn[i] << " ";
	}
	cout << endl;
	cout << "Error : " << this->error << " OutputValue : " << this->outputValue << endl;
}
