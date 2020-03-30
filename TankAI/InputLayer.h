#pragma once

#include <vector>
#include <iostream>
#include "MathUtils.h"
using namespace std;

class InputLayer
{
public:
	InputLayer();
	~InputLayer();

	vector<double> inputValues;

	vector<double> calculateLayerOutputData();
	void feedInput(vector<double> inputValues);
	void printInputLayer();
private:

};

inline InputLayer::InputLayer()
{
}

inline InputLayer::~InputLayer()
{
}

inline vector<double> InputLayer::calculateLayerOutputData()
{
	for (int i = 0; i < this->inputValues.size();++i)
	{
		this->inputValues[i] = MathUtils::sigmoid(this->inputValues[i]);
	}
	return this->inputValues;
}

inline void InputLayer::feedInput(vector<double> inputValues)
{
	this->inputValues = inputValues;
}

inline void InputLayer::printInputLayer()
{
	cout << " INPUT LAYER " << endl << endl;
	for (int i = 0;i < this->inputValues.size();++i)
	{
		cout << " Value " << i << " : " << this->inputValues[i] << endl;
	}
	cout << endl;
}
