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
	Neuron(int numberOfConnections);
	~Neuron();

	double error;
	double gamma;
	double outputValue;
	double bias;
	
	vector<double> weightsIn;
	vector<double> weightsDelta;


	double calculateOutputValue(vector<double> inputs);
	void printNeuron();

private:

};

inline Neuron::Neuron(int numberOfConnections)
{
	bias = 1.0;
	for (int i = 0; i < numberOfConnections; ++i)
	{
		weightsIn.push_back(((double)rand() / (RAND_MAX)));
		weightsDelta.push_back(0);
	}
	this->error = 0;
}

inline Neuron::~Neuron()
{
}

inline double Neuron::calculateOutputValue(vector<double> inputs)
{
	double tempOutputValue = 0;

	for (int i = 0;i < inputs.size();++i)
	{
		tempOutputValue += inputs[i] * weightsIn[i];
	}
	this->outputValue = MathUtils::sigmoid(tempOutputValue+bias);
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
