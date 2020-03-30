#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

class Neuron
{
public:
	Neuron(int numberOfConnections);
	~Neuron();

	double error;
	double outputValue;
	
	vector<double> weightsIn;

	double calculateOutputValue(vector<double> inputs);
	void printNeuron();

private:

};

inline Neuron::Neuron(int numberOfConnections)
{
	for (int i = 0; i < numberOfConnections; ++i)
	{
		weightsIn.push_back((double)rand() / (RAND_MAX));
	}
	error = 0;
}

inline Neuron::~Neuron()
{
}

inline double Neuron::calculateOutputValue(vector<double> inputs)
{
	double tempOutputValue = 0.0;

	for (int i = 0;i < inputs.size();++i)
	{
		tempOutputValue += inputs[i] * weightsIn[i];
	}

	this->outputValue = tempOutputValue;
	return this->outputValue;
}

inline void Neuron::printNeuron()
{
	for (int i = 0; i < weightsIn.size();++i)
	{
		cout << "W" << i << " : " << weightsIn[i] << " ";
	}
}
