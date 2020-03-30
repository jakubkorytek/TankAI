#pragma once

#include <vector>

using namespace std;

class TrainingData
{
public:
	TrainingData(vector<double> inputs, double output);
	~TrainingData();

	vector<double> inputs;
	double output;

private:

};

inline TrainingData::TrainingData(vector<double> inputs, double output)
{
	this->inputs = inputs;
	this->output = output;
}

inline TrainingData::~TrainingData()
{
}
