#pragma once

#include <vector>

using namespace std;

class TrainingData
{
public:
	TrainingData() {};
	TrainingData(vector<double> inputs, double output);
	~TrainingData();

	vector<double> inputs;
	vector<double> output;

private:

};

inline TrainingData::TrainingData(vector<double> inputs, double output)
{
	this->inputs = inputs;
	this->output.push_back(output);
}

inline TrainingData::~TrainingData()
{
}
